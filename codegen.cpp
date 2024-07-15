#include "codegen.hpp"

#include <array>

CodeGenerator::CodeGenerator() : the_context(std::make_unique<llvm::LLVMContext>()),
                                 the_module(std::make_unique<llvm::Module>("C-Compiler", *the_context)),
                                 builder(std::make_unique<llvm::IRBuilder<llvm::NoFolder>>(*the_context)),
                                 in_global_scope(true)
{
    generate_prelude();
}

/**
 * Before we actually get to code generation, our compiler should define some global variables and function which
 * all programs have access to. For now, the only function accessible is Output(i32) which outputs the given int to terminal.
 * You can view the generated code in prelude.ll file.
 */
void CodeGenerator::generate_prelude()
{
    // First we declare a global variable of chars which holds "%d\n\0".
    auto format_string_type = llvm::ArrayType::get(llvm::Type::getInt8Ty(*this->the_context), 4);
    std::array format_string_bytes{
        static_cast<llvm::Constant *>(llvm::ConstantInt::get(llvm::Type::getInt8Ty(*this->the_context), '%')),
        static_cast<llvm::Constant *>(llvm::ConstantInt::get(llvm::Type::getInt8Ty(*this->the_context), 'd')),
        static_cast<llvm::Constant *>(llvm::ConstantInt::get(llvm::Type::getInt8Ty(*this->the_context), '\n')),
        static_cast<llvm::Constant *>(llvm::ConstantInt::get(llvm::Type::getInt8Ty(*this->the_context), '\0')),
    };
    auto format_string_value = llvm::ConstantArray::get(format_string_type, llvm::ArrayRef(format_string_bytes));
    // NOTE: this value is declared with new to outlive the program. I should not be freed until the very end
    auto number_format = new llvm::GlobalVariable(*this->the_module, format_string_type, true, llvm::GlobalValue::LinkageTypes::PrivateLinkage, format_string_value, "number_format");
    // Declare the printf function from standard C library
    std::array printf_function_arguments{
        static_cast<llvm::Type *>(llvm::PointerType::getUnqual(format_string_type)),
    };
    auto printf_function_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(*this->the_context), llvm::ArrayRef(printf_function_arguments), true);
    auto printf_function = llvm::Function::Create(printf_function_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "printf", this->the_module.get());
    // Declare the output function which simply prints an int
    std::array output_function_arguments{
        static_cast<llvm::Type *>(llvm::Type::getInt32Ty(*this->the_context)),
    };
    auto output_function_type = llvm::FunctionType::get(llvm::Type::getVoidTy(*this->the_context), llvm::ArrayRef(output_function_arguments), false);
    auto output_function = llvm::Function::Create(output_function_type, llvm::GlobalValue::LinkageTypes::PrivateLinkage, "output", this->the_module.get());
    output_function->getArg(0)->setName("a");
    // In the output function, call the printf function
    auto output_function_block = llvm::BasicBlock::Create(*this->the_context, "", output_function);
    this->builder->SetInsertPoint(output_function_block);
    std::array output_function_call_arguments{
        // the string format and the number
        static_cast<llvm::Value *>(number_format),
        static_cast<llvm::Value *>(output_function->getArg(0)),
    };
    this->builder->CreateCall(printf_function, llvm::ArrayRef(output_function_call_arguments));
    this->builder->CreateRet(nullptr); // ret void
}

void CodeGenerator::print_code()
{
    this->the_module->print(llvm::errs(), nullptr);
}

/**
 * Void type is used when the declaring type is void. It simply pushes VariableType::VOID to ss
 */
void CodeGenerator::void_type()
{
    this->semantic_stack.push_back(VariableType::VOID);
}

/**
 * Void type is used when the declaring type is int. It simply pushes VariableType::INT to ss
 */
void CodeGenerator::int_type()
{
    this->semantic_stack.push_back(VariableType::INT);
}

/**
 * This method is used to save the pid of the new declaring variable in the declaring_pid_name.
 * It simply copies the value to the declaring_pid_name. It also checks if the variable was declared before or not.
 */
void CodeGenerator::declaring_pid(const char *pid)
{
    this->declaring_pid_name = pid;
    // TODO: check if variable was defined before
}

/**
 * There are two ways a variable can be declared. Either it's a global variable or a local one. If this is a global
 * variable, we have to explicitly tell LLVM to generate code for it. Otherwise, we simply generate a code to assign
 * zero to a local variable.
 *
 * We could have made this in a way that something should assign to a variable before using it however, I think
 * going with Golang style is better. It's my language and I'll do whatever I want.
 */
void CodeGenerator::variable_declared()
{
    assert(!this->declaring_pid_name.empty()); // something should be declared
    assert(std::get<CodeGenerator::VariableType>(this->semantic_stack.back()) == CodeGenerator::VariableType::INT);
    this->semantic_stack.pop_back(); // pop the int from stack

    auto zero = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*this->the_context), 0, true);
    if (this->in_global_scope)
    {
        // Check if a previous global variable is declared using the name
        assert(!this->the_module->getNamedGlobal(this->declaring_pid_name));
        // Create the global variable
        new llvm::GlobalVariable(*this->the_module, llvm::Type::getInt32Ty(*this->the_context), false, llvm::GlobalValue::LinkageTypes::InternalLinkage, zero, this->declaring_pid_name);
    }
    else
    {
        // Check if a previous local variable is declared using the name
        assert(this->local_variables.count(this->declaring_pid_name) == 0);
        // Create an add instruction with zero operands to assign a new variable
        auto created_value = this->builder->CreateOr(zero, zero, this->declaring_pid_name);
        this->local_variables.emplace(std::move(this->declaring_pid_name), created_value);
    }
    this->declaring_pid_name.clear();
}

void CodeGenerator::array_declared()
{
    assert((!this->declaring_pid_name.empty()));                 // something should be declared
    int array_size = std::get<int>(this->semantic_stack.back()); // get the size of the array
    this->semantic_stack.pop_back();                             // pop the size
    assert(std::get<CodeGenerator::VariableType>(this->semantic_stack.back()) == CodeGenerator::VariableType::INT);
    this->semantic_stack.pop_back(); // pop the int from stack

    auto array_type = llvm::ArrayType::get(llvm::Type::getInt32Ty(*this->the_context), array_size);
    if (this->in_global_scope)
    {
        // Check if a previous global variable is declared using the name
        assert(!this->the_module->getNamedGlobal(this->declaring_pid_name));
        // Create the global variable
        new llvm::GlobalVariable(*this->the_module, array_type, false, llvm::GlobalValue::LinkageTypes::InternalLinkage, llvm::ConstantAggregateZero::get(array_type), this->declaring_pid_name);
    }
    else
    {
        // Check if a previous local variable is declared using the name
        assert(this->local_variables.count(this->declaring_pid_name) == 0);
        // Allocate memory on stack
        auto one_value = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*this->the_context), 1, true);
        auto alloca = this->builder->CreateAlloca(array_type, one_value, this->declaring_pid_name);
        this->local_variables.emplace(std::move(this->declaring_pid_name), alloca);
    }
    this->declaring_pid_name.clear();
}

/**
 * When the function declaration begins, we only check some assertions and states and then move out of the
 * global scope to local scope.
 *
 * NOTE: On top of ss, we have INT or VOID which is the return type of the function.
 */
void CodeGenerator::function_start()
{
    assert(this->in_global_scope);
    assert(!this->declaring_pid_name.empty());
    assert(this->declaring_function_name.empty());
    assert(this->declaring_function_params.empty());
    assert(this->local_variables.empty());

    this->declaring_function_name = std::move(this->declaring_pid_name);
    this->in_global_scope = false;
    this->declaring_pid_name.clear();
}

/**
 * Called when an int parameter is declared as an argument of function.
 */
void CodeGenerator::int_param()
{
    assert(!this->declaring_pid_name.empty());
    assert(!this->declaring_function_name.empty());

    this->declaring_function_params.push_back(DeclaringFunctionParameterData{
        std::move(this->declaring_pid_name),
        llvm::Type::getInt32Ty(*this->the_context)});
    this->declaring_pid_name.clear();
}

/**
 * Called when an array parameter is declared as an argument of function.
 */
void CodeGenerator::array_param()
{
    assert(!this->declaring_pid_name.empty());
    assert(!this->declaring_function_name.empty());

    this->declaring_function_params.push_back(DeclaringFunctionParameterData{
        std::move(this->declaring_pid_name),
        llvm::Type::getInt32PtrTy(*this->the_context)});
    this->declaring_pid_name.clear();
}

/**
 * When the function param declerations end, we shall create the prototype of the function.
 *
 * First, we should gather all of the arguments and create the argument list
 * of types and their names. Then we should look at the top of ss and find out
 * the return type of the function and at last, insert all parameters in local_variables
 * map.
 *
 * Then, some cleanups should be done (emptying variables).
 */
void CodeGenerator::function_params_end()
{
    assert(this->declaring_pid_name.empty());
    assert(!this->declaring_function_name.empty());
    auto return_type = std::get<CodeGenerator::VariableType>(this->semantic_stack.back());
    this->semantic_stack.pop_back();

    // Generate a list of argument types
    std::vector<llvm::Type *> param_types;
    param_types.reserve(this->declaring_function_params.size());
    for (const auto &param : this->declaring_function_params)
        param_types.push_back(param.type);
    // Get the return type
    llvm::Type *llvm_return_type = return_type == CodeGenerator::VariableType::VOID ? llvm::Type::getVoidTy(*this->the_context) : llvm::Type::getInt32Ty(*this->the_context);
    // Generate the function
    auto function_type = llvm::FunctionType::get(llvm_return_type, llvm::ArrayRef(param_types), false);
    auto declared_function = llvm::Function::Create(function_type, llvm::GlobalValue::LinkageTypes::PrivateLinkage, this->declaring_function_name, this->the_module.get());
    for (size_t i = 0; i < this->declaring_function_params.size(); i++)
    {
        auto argument = declared_function->getArg(i);
        argument->setName(this->declaring_function_params.at(i).name);

        // Insert into local parameters map
        this->local_variables.emplace(std::move(this->declaring_function_params.at(i).name), argument);
    }

    // Move the insert point to entry of function
    auto entry_function_block = llvm::BasicBlock::Create(*this->the_context, "", declared_function);
    this->builder->SetInsertPoint(entry_function_block);

    // Cleanup stuff
    this->declaring_function_params.clear();
    this->declaring_function_name.clear();
}

/**
 * When the function declaration ends, we simply move to global scope and clear
 * the list of local variables.
 */
void CodeGenerator::function_end()
{
    assert(!this->in_global_scope);

    in_global_scope = true;
    this->local_variables.clear();
}

/**
 * Immediate will push the immediate argument to the stack.
 */
void CodeGenerator::immediate(int imm)
{
    this->semantic_stack.push_back(imm);
}