#include "codegen.hpp"

#include <llvm/IR/Instructions.h>

#include <array>
#include <cassert>

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
    auto print_format_string_type = llvm::ArrayType::get(llvm::Type::getInt8Ty(*this->the_context), 4);
    std::array print_format_string_bytes{
        static_cast<llvm::Constant *>(llvm::ConstantInt::get(llvm::Type::getInt8Ty(*this->the_context), '%')),
        static_cast<llvm::Constant *>(llvm::ConstantInt::get(llvm::Type::getInt8Ty(*this->the_context), 'd')),
        static_cast<llvm::Constant *>(llvm::ConstantInt::get(llvm::Type::getInt8Ty(*this->the_context), '\n')),
        static_cast<llvm::Constant *>(llvm::ConstantInt::get(llvm::Type::getInt8Ty(*this->the_context), '\0')),
    };
    auto print_format_string_value = llvm::ConstantArray::get(print_format_string_type, llvm::ArrayRef(print_format_string_bytes));
    // NOTE: this value is declared with new to outlive the program. I should not be freed until the very end
    auto printf_number_format = new llvm::GlobalVariable(*this->the_module, print_format_string_type, true, llvm::GlobalValue::LinkageTypes::PrivateLinkage, print_format_string_value, "print_number_format");
    // The same thing for the input function. It holds "%d\0".
    auto scanf_format_string_type = llvm::ArrayType::get(llvm::Type::getInt8Ty(*this->the_context), 3);
    std::array scanf_format_string_bytes{
        static_cast<llvm::Constant *>(llvm::ConstantInt::get(llvm::Type::getInt8Ty(*this->the_context), '%')),
        static_cast<llvm::Constant *>(llvm::ConstantInt::get(llvm::Type::getInt8Ty(*this->the_context), 'd')),
        static_cast<llvm::Constant *>(llvm::ConstantInt::get(llvm::Type::getInt8Ty(*this->the_context), '\0')),
    };
    auto scanf_format_string_value = llvm::ConstantArray::get(scanf_format_string_type, llvm::ArrayRef(scanf_format_string_bytes));
    auto scanf_number_format = new llvm::GlobalVariable(*this->the_module, scanf_format_string_type, true, llvm::GlobalValue::LinkageTypes::PrivateLinkage, scanf_format_string_value, "scanf_number_format");    
    // Declare the printf and scanf functions from standard C library
    std::array printf_scanf_function_arguments{
        static_cast<llvm::Type *>(llvm::PointerType::getUnqual(print_format_string_type)),
    };
    auto printf_scanf_function_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(*this->the_context), llvm::ArrayRef(printf_scanf_function_arguments), true);
    auto printf_function = llvm::Function::Create(printf_scanf_function_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "printf", this->the_module.get());
    auto scanf_function = llvm::Function::Create(printf_scanf_function_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "scanf", this->the_module.get());
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
        static_cast<llvm::Value *>(printf_number_format),
        static_cast<llvm::Value *>(output_function->getArg(0)),
    };
    this->builder->CreateCall(printf_function, llvm::ArrayRef(output_function_call_arguments));
    this->builder->CreateRet(nullptr); // ret void
    // Declare the input function which simply reads an int from stdin using scanf
    auto input_function_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(*this->the_context), false);
    auto input_function = llvm::Function::Create(input_function_type, llvm::GlobalValue::LinkageTypes::PrivateLinkage, "input", this->the_module.get());
    auto input_function_block = llvm::BasicBlock::Create(*this->the_context, "", input_function);
    this->builder->SetInsertPoint(input_function_block);
    // First allocate an int on the stack to get the pointer of it
    auto input_result = this->builder->CreateAlloca(llvm::Type::getInt32Ty(*this->the_context));
    std::array input_function_call_arguments{
        // the string format and the number pointer
        static_cast<llvm::Value *>(scanf_number_format),
        static_cast<llvm::Value *>(input_result),
    };
    this->builder->CreateCall(scanf_function, llvm::ArrayRef(input_function_call_arguments));
    auto input_result_reg = this->builder->CreateLoad(llvm::Type::getInt32Ty(*this->the_context), input_result);
    this->builder->CreateRet(input_result_reg);
}

void CodeGenerator::print_code(const char *output_filename)
{
    std::error_code error_code;
    auto output = llvm::raw_fd_ostream(output_filename, error_code);
    if (!error_code)
        this->the_module->print(output, nullptr);
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
        // Create the local variable as a zero sized array
        auto one_value = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*this->the_context), 1, true);
        auto alloca = this->builder->CreateAlloca(llvm::Type::getInt32Ty(*this->the_context), one_value, this->declaring_pid_name);
        this->local_variables.emplace(std::move(this->declaring_pid_name), alloca);
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
    // We dont pop the return type now. We still need it in the function_end for implicit return

    // Generate a list of argument types
    std::vector<llvm::Type *> param_types;
    param_types.reserve(this->declaring_function_params.size());
    for (const auto &param : this->declaring_function_params)
        param_types.push_back(param.type);
    // Get the return type
    llvm::Type *llvm_return_type = return_type == CodeGenerator::VariableType::VOID ? llvm::Type::getVoidTy(*this->the_context) : llvm::Type::getInt32Ty(*this->the_context);
    // Generate the function
    auto function_type = llvm::FunctionType::get(llvm_return_type, llvm::ArrayRef(param_types), false);
    auto declared_function = llvm::Function::Create(function_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, this->declaring_function_name, this->the_module.get());

    // Move the insert point to entry of function
    auto entry_function_block = llvm::BasicBlock::Create(*this->the_context, "", declared_function);
    this->builder->SetInsertPoint(entry_function_block);

    // At the very first of the function declare the arguments as local variables
    auto one_value = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*this->the_context), 1, true);
    for (size_t i = 0; i < this->declaring_function_params.size(); i++)
    {
        auto argument = declared_function->getArg(i);
        // If this value is an int, then we put it in a stack variable and work with that
        if (argument->getType() == llvm::Type::getInt32Ty(*this->the_context))
        {
            // Create a alloc for each argument to store the param in stack
            auto alloca = this->builder->CreateAlloca(argument->getType(), one_value, this->declaring_function_params.at(i).name);
            // Create an instruction to store the argument in the memory
            this->builder->CreateStore(argument, alloca);
            // Insert into local parameters map
            this->local_variables.emplace(std::move(this->declaring_function_params.at(i).name), alloca);
        }
        else
        {
            // Otherwise, we don't store the pointer in the stack variable. Instead, because pointers
            // are immutable in this language, we simply use the value of the argument.
            assert(argument->getType() == llvm::Type::getInt32PtrTy(*this->the_context));
            argument->setName(this->declaring_function_params.at(i).name);
            this->local_variables.emplace(std::move(this->declaring_function_params.at(i).name), argument);
        }
    }

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
    auto return_type = std::get<CodeGenerator::VariableType>(this->semantic_stack.back());
    this->semantic_stack.pop_back();

    in_global_scope = true;
    this->local_variables.clear();
    if (return_type == CodeGenerator::VariableType::VOID)
        this->builder->CreateRet(nullptr); // create an implicit ret void
    else if (return_type == CodeGenerator::VariableType::INT)
        this->builder->CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*this->the_context.get()), 0, true)); // create an implicit ret 0
    else
        assert(false && "Unknown return type");
}

/**
 * Immediate will push the immediate argument to the stack.
 */
void CodeGenerator::immediate(int imm)
{
    this->semantic_stack.push_back(imm);
}

/**
 * pid will search the name in the local scope and then the global scope
 * and then push the value of it in the semnatic stack.
 *
 * If the variable is not found, the program aborts.
 */
void CodeGenerator::pid(const char *pid)
{
    const std::string pid_string(pid);
    // Look in local scope
    auto local_variable = this->local_variables.find(pid_string);
    if (local_variable != this->local_variables.end())
    {
        this->semantic_stack.push_back(local_variable->second);
        return;
    }
    // Look in global scope
    auto global_variable = this->the_module->getNamedGlobal(pid_string);
    if (global_variable != nullptr)
    {
        this->semantic_stack.push_back(global_variable);
        return;
    }
    // Is this a function?
    auto function_call = this->the_module->getFunction(pid_string);
    assert(function_call);
    this->semantic_stack.push_back(function_call);
}

/**
 * Pops the result of an expression from stack.
 */
void CodeGenerator::pop_expression()
{
    // Works like an assertion
    std::get<llvm::Value *>(this->semantic_stack.back());
    this->semantic_stack.pop_back();
}

/**
 * This function will receive an value which is either a pointer to data or a register
 * (i32). If the input is a register, it will simply return the input. Otherwise, a
 * load instruction is inserted and the result is returned. This means that the output
 * of this function is always an i32 value in a register.
 *
 * This function is used when the result of an array or a register is used to calculate
 * a right hand side of an expression. For assigning, this task is done in assign itself.
 * This function is also handy to get the value of global variables.
 *
 * One more important thing is that global variables are also pointers. This means that
 * a load instruction will also be generated if you pass a global variable to this function.
 */
llvm::Value *CodeGenerator::dereference_ptr_if_needed(llvm::Value *value)
{
    auto type = value->getType();
    if (type == llvm::Type::getInt32Ty(*this->the_context))
        return value;
    if (type == llvm::Type::getInt32PtrTy(*this->the_context))
    {
        // Generate a load instruction to load the data in a register
        return this->builder->CreateLoad(llvm::Type::getInt32Ty(*this->the_context), value);
    }
    assert(false);
}

/**
 * When assign is called, the top of the stack is the source and the next
 * variable in the stack is the destination.
 *
 * To assign, however, we should consider that the destination and source MIGHT be
 * array references. In this case, we should do pointer stuff such as using load
 * and store instructions.
 *
 * If the destination is a register, we create an Or instruction with zero and the
 * source value and put the result in the destination. If the destination is pointer,
 * we use the store instruction. The later happens in three cases: 1. Global int variable
 * 2. Pointer to element of local array 3. Pointer to element of global array
 */
void CodeGenerator::assign()
{
    // Get the stuff we need to assign
    auto source = std::get<llvm::Value *>(this->semantic_stack.back());
    this->semantic_stack.pop_back();
    auto destination = std::get<llvm::Value *>(this->semantic_stack.back());
    this->semantic_stack.pop_back();
    // The source must be in a register
    llvm::Value *source_in_reg = this->dereference_ptr_if_needed(source);
    // The assigned value must be a pointer. Because all variables (global or local) are pointers
    assert(destination->getType() == llvm::Type::getInt32PtrTy(*this->the_context));
    // In all cases, we can simply omit an store instruction to store the result in the desired location.
    this->builder->CreateStore(source_in_reg, destination);
    // Put the result back in the semantic stack.
    this->semantic_stack.push_back(destination);
}

/**
 * Array is used to find the pointer to the requested element of specific array.
 * It is called when the top of the semantic stack contains the value of the index
 * of the array and the next value in the stack contains the pointer to the stack.
 */
void CodeGenerator::array()
{
    // Get the stuff we need to assign
    auto index = std::get<llvm::Value *>(this->semantic_stack.back());
    this->semantic_stack.pop_back();
    auto ptr = std::get<llvm::Value *>(this->semantic_stack.back());
    this->semantic_stack.pop_back();
    assert(ptr->getType() == llvm::Type::getInt32PtrTy(*this->the_context));

    // Get the real index in register
    llvm::Value *index_in_reg = this->dereference_ptr_if_needed(index);
    // Calculate the offset
    const std::array index_arr{
        index_in_reg,
    };
    auto offset_ptr = llvm::GetElementPtrInst::CreateInBounds(
        llvm::Type::getInt32Ty(*this->the_context),
        ptr, llvm::ArrayRef<llvm::Value *>(index_arr),
        "",
        this->builder->GetInsertBlock());

    // Push the result in ss
    this->semantic_stack.push_back(offset_ptr);
}

/**
 * Pushes an immediate value in the stack as llvm::Value
 */
void CodeGenerator::immediate_val(int num)
{
    this->semantic_stack.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*this->the_context), static_cast<uint64_t>(num), true));
}

/**
 * This function will simply store an operator in the operator stack.
 */
void CodeGenerator::save_operator(CodeGenerator::Operator op)
{
    this->operator_stack.push_back(op);
}

/**
 * Negate will get the top of the semantic stack, generate a code to negate it,
 * and then put the result back in the semantic stack.
 */
void CodeGenerator::negate()
{
    // Get the value
    auto value = std::get<llvm::Value *>(this->semantic_stack.back());
    this->semantic_stack.pop_back();

    // Generate code to negate it
    llvm::Value *value_in_reg = this->dereference_ptr_if_needed(value);
    auto result = this->builder->CreateNeg(value_in_reg);

    // Insert the result back in the semantic stack
    this->semantic_stack.push_back(result);
}

/**
 * Calculate will generate code to do the arithmetic based on the two top values in the stack
 * and the top value in the operator stack. It will pop the two values from the top of the
 * semantic stack, dereference them if needed, and does the calculation based on the
 * input code. The result of the calculation is pushed back on the semantic stack. It is
 * always a register (temporary) in the local scope.
 */
void CodeGenerator::calculate()
{
    // Get the variables needed
    auto operand2 = std::get<llvm::Value *>(this->semantic_stack.back());
    this->semantic_stack.pop_back();
    auto operand1 = std::get<llvm::Value *>(this->semantic_stack.back());
    this->semantic_stack.pop_back();
    auto op = this->operator_stack.back();
    this->operator_stack.pop_back();

    // Dereference pointers
    operand1 = this->dereference_ptr_if_needed(operand1);
    operand2 = this->dereference_ptr_if_needed(operand2);

    // Check what we should do
    llvm::Value *result;
    switch (op)
    {
    case CodeGenerator::Operator::PLUS:
        result = this->builder->CreateAdd(operand1, operand2);
        break;
    case CodeGenerator::Operator::MINUS:
        result = this->builder->CreateSub(operand1, operand2);
        break;
    case CodeGenerator::Operator::MULT:
        result = this->builder->CreateMul(operand1, operand2);
        break;
    case CodeGenerator::Operator::LESS_THAN:
        result = this->builder->CreateZExt(
            this->builder->CreateICmpSLT(operand1, operand2),
            llvm::Type::getInt32Ty(*this->the_context));
        break;
    case CodeGenerator::Operator::EQUALS:
        result = this->builder->CreateZExt(
            this->builder->CreateICmpEQ(operand1, operand2),
            llvm::Type::getInt32Ty(*this->the_context));
        break;
    default:
        assert(false);
    }

    // Put the result back in the stack
    this->semantic_stack.push_back(result);
}

/**
 * Call is called just after the argument declaration of a function call.
 * At this point, the semantic stack contains some llvm::Values and then a llvm::Function
 * which is the function we should call. Our strategy is popping from the stack and storing the
 * arguments (llvm::Value *) in an array until we reach the llvm::Function. At this
 * point we can insert the call instruction and jump to the function.
 *
 * It's also worth noting that the result of the function is stored in the semantic stack.
 * If the function is void, we will push a zero into the stack because it will be popped
 * after the expression is finished. This however, will create some bugs if you assign
 * the result of a void function to a variable which results in that variable be assigned zero.
 * This behaviour should be later be reported in the semantic analyzer.
 */
void CodeGenerator::call()
{
    // Get the list of arguments
    std::vector<llvm::Value *> arguments;
    while (std::holds_alternative<llvm::Value *>(this->semantic_stack.back()))
    {
        arguments.push_back(std::get<llvm::Value *>(this->semantic_stack.back()));
        this->semantic_stack.pop_back();
    }
    std::reverse(arguments.begin(), arguments.end());
    // The next value should be the function
    auto function_to_call = std::get<llvm::Function *>(this->semantic_stack.back());
    this->semantic_stack.pop_back();
    // Fix the arguments if needed (dereference pointers)
    assert(arguments.size() == function_to_call->arg_size());
    int arg_count = 0;
    for (auto const &argument : function_to_call->args())
    {
        if (argument.getType() == llvm::Type::getInt32Ty(*this->the_context)) // if this is an int, dereference it
            arguments[arg_count] = this->dereference_ptr_if_needed(arguments[arg_count]);
        arg_count++;
    }
    // Just create the call instruction
    auto returned_value = this->builder->CreateCall(function_to_call, llvm::ArrayRef(arguments));
    if (returned_value->getType() == llvm::Type::getVoidTy(*this->the_context)) // if void, push zero
        this->semantic_stack.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*this->the_context), static_cast<uint64_t>(0), true));
    else
        this->semantic_stack.push_back(returned_value);
}

/**
 * This function will simply generate a return instruction.
 *
 * If the is_void parameter is true, it will emit a 'ret void' instruction.
 * Otherwise, the top of the semantic stack is returned as the return value.
 *
 * Also, after inserting the return function we enter an "unreachable" block
 * to trap everything after the return function.
 */
void CodeGenerator::insert_return(bool is_void)
{
    this->builder->CreateRet(is_void ? nullptr : this->dereference_ptr_if_needed(std::get<llvm::Value *>(this->semantic_stack.back())));
    if (!is_void)
        this->semantic_stack.pop_back();
    // Insert an unreachable block
    this->builder->SetInsertPoint(
        llvm::BasicBlock::Create(*this->the_context.get(), "unreachable", this->builder->GetInsertBlock()->getParent()));
}

/**
 * The if condition is called as soon as the branch of the if condition is finished and the top of the stack is the
 * condition. Here, we do declare every basic block for if and else and then start filling them.
 */
void CodeGenerator::if_condition()
{
    // Get the expression result
    auto condition = std::get<llvm::Value *>(this->semantic_stack.back());
    this->semantic_stack.pop_back();
    // Convert condition to bit
    condition = this->dereference_ptr_if_needed(condition);
    condition = this->builder->CreateICmpNE(condition, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*this->the_context.get()), 0, true));
    // Create the basic blocks
    IfElseBasicBlocks blocks;
    blocks.then_block = llvm::BasicBlock::Create(*this->the_context.get(), "then", this->builder->GetInsertBlock()->getParent());
    blocks.else_block = llvm::BasicBlock::Create(*this->the_context.get(), "else", this->builder->GetInsertBlock()->getParent());
    blocks.aftermath_block = llvm::BasicBlock::Create(*this->the_context.get(), "aftermath", this->builder->GetInsertBlock()->getParent());
    // Create the condition jump
    this->builder->CreateCondBr(condition, blocks.then_block, blocks.else_block);
    // Then, we start emitting code for the "then" block
    this->builder->SetInsertPoint(blocks.then_block);
    // Push the blocks into stack to handle nested ifs
    this->semantic_stack.push_back(blocks);
}

/**
 * This value is called if we have an if condition without "else" statement.
 * In this case, we fill the else statement with a simple jump to aftermath and
 * set the builder to omit in the aftermath code block.
 *
 * We should also pop the semantic stack because this if statement is finished.
 */
void CodeGenerator::if_no_else_end()
{
    // Get the blocks
    auto blocks = std::get<IfElseBasicBlocks>(this->semantic_stack.back());
    this->semantic_stack.pop_back();
    // Get the function
    auto this_function = this->builder->GetInsertBlock()->getParent();
    // Jump to aftermath from the "then" block
    this->builder->CreateBr(blocks.aftermath_block);
    // In the else, just jump to aftermath as well
    this->builder->SetInsertPoint(blocks.else_block);
    this->builder->CreateBr(blocks.aftermath_block);
    // Move the pointer of the next instruction to aftermath block
    this->builder->SetInsertPoint(blocks.aftermath_block);
}

/**
 * This function is called as soon as the "else" statement is beginning.
 * In this case, we should finish the "then" block with a branch to the aftermath
 * and then move the builder insert point to the else branch.
 */
void CodeGenerator::if_else_begin()
{
    // Get the blocks
    auto blocks = std::get<IfElseBasicBlocks>(this->semantic_stack.back());
    // Jump to aftermath from the "then" block
    this->builder->CreateBr(blocks.aftermath_block);
    // Just set the insert point to "else" block
    this->builder->SetInsertPoint(blocks.else_block);
}

/**
 * This function is called after an if statement is finishing with an "else" statement.
 * This means that we should at first pop the blocks from the semantic stack and
 * and then create a branch to the aftermath block and move the insert point to it.
 */
void CodeGenerator::if_else_end()
{
    // Get the blocks
    auto blocks = std::get<IfElseBasicBlocks>(this->semantic_stack.back());
    this->semantic_stack.pop_back();
    // Jump to aftermath from the "else" block
    this->builder->CreateBr(blocks.aftermath_block);
    // Just set the insert point to "aftermath" block
    this->builder->SetInsertPoint(blocks.aftermath_block);
}

/**
 * This function marks the start of a for loop.
 * In this function, we create the basic blocks and jump to the condition block.
 */
void CodeGenerator::for_condition_begin()
{
    // Create the basic blocks
    ForLoopBasicBlocks blocks;
    blocks.condition_block = llvm::BasicBlock::Create(*this->the_context.get(), "condition", this->builder->GetInsertBlock()->getParent());
    blocks.step_block = llvm::BasicBlock::Create(*this->the_context.get(), "step", this->builder->GetInsertBlock()->getParent());
    blocks.body_block = llvm::BasicBlock::Create(*this->the_context.get(), "body", this->builder->GetInsertBlock()->getParent());
    blocks.aftermath_block = llvm::BasicBlock::Create(*this->the_context.get(), "aftermath", this->builder->GetInsertBlock()->getParent());
    // From the initial block (which is unamed) jump to the condition block
    this->builder->CreateBr(blocks.condition_block);
    // Then, we start emitting code for the condition block
    this->builder->SetInsertPoint(blocks.condition_block);
    // Push the blocks into stack to handle nested for loops
    this->semantic_stack.push_back(blocks);
}

/**
 * When the condition ends, we have a number on top of the semantic stack and the basic blocks
 * of the for loop in the next element in the semantic stack. So we do a conditional branch to
 * either the aftermath block or the loop body.
 *
 * Then we move the insertion point to the step block.
 */
void CodeGenerator::for_condition_end()
{
    // Get the expression result
    auto condition = std::get<llvm::Value *>(this->semantic_stack.back());
    this->semantic_stack.pop_back();
    // Get the blocks
    auto for_blocks = std::get<ForLoopBasicBlocks>(this->semantic_stack.back());
    // Compare with zero and jump
    condition = this->dereference_ptr_if_needed(condition);
    condition = this->builder->CreateICmpNE(condition, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*this->the_context.get()), 0, true));
    // Create the condition jump
    this->builder->CreateCondBr(condition, for_blocks.body_block, for_blocks.aftermath_block);
    // Then create the code for step
    this->builder->SetInsertPoint(for_blocks.step_block);
}

/**
 * When the step of the for loop ends and the body starts, we should only move the
 * insertion point to the for body and after the condition, jump to the condition.
 */
void CodeGenerator::for_step_end()
{
    auto for_blocks = std::get<ForLoopBasicBlocks>(this->semantic_stack.back());
    this->builder->CreateBr(for_blocks.condition_block);
    this->builder->SetInsertPoint(for_blocks.body_block);
}

/**
 * After the for loop ends, we should just insert an unconditional branch to the step
 * and then pop the information about the for loop from the stack. We should also
 * move the insertion point to the aftermath.
 */
void CodeGenerator::for_end()
{
    auto for_blocks = std::get<ForLoopBasicBlocks>(this->semantic_stack.back());
    this->semantic_stack.pop_back(); // note that we pop the value from the stack
    this->builder->CreateBr(for_blocks.step_block);
    this->builder->SetInsertPoint(for_blocks.aftermath_block);
}

/**
 * This code is used to insert a break statement in the code.
 * What the break statement does is that it searches the semantic stack for
 * a for loop and inserts a jump to the aftermath block. It also enters an unreachable
 * block because every other instruction after this is unreachable.
 */
void CodeGenerator::insert_break()
{
    // Search for the for loop in the semantic stack
    bool found = false;
    for (auto i = this->semantic_stack.crbegin(); i != this->semantic_stack.crend(); i++)
    {
        if (std::holds_alternative<ForLoopBasicBlocks>(*i))
        {
            this->builder->CreateBr(std::get<ForLoopBasicBlocks>(*i).aftermath_block); // jump to end
            found = true;
            break;
        }
    }
    assert(found);
    // Insert an unreachable block
    this->builder->SetInsertPoint(
        llvm::BasicBlock::Create(*this->the_context.get(), "unreachable", this->builder->GetInsertBlock()->getParent()));
}