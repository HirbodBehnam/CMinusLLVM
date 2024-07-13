#include "codegen.hpp"

#include <array>

CodeGenerator::CodeGenerator() : the_context(std::make_unique<llvm::LLVMContext>()),
                                 the_module(std::make_unique<llvm::Module>("C-Compiler", *the_context)),
                                 builder(std::make_unique<llvm::IRBuilder<>>(*the_context)),
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
        assert(false);
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
        assert(false);
    }
    this->declaring_pid_name.clear();
}

/**
 * Immediate will push the immediate argument to the stack.
 */
void CodeGenerator::immediate(int imm)
{
    this->semantic_stack.push_back(imm);
}