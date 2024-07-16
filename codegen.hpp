#include "Parser.hpp"
#include "Lexer.hpp"

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/NoFolder.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <memory>
#include <string>
#include <variant>
#include <vector>
#include <unordered_map>

/**
 * DeclaringFunctionParameterData is a data container which holds the metadata needed
 * for each declared parameter of a function.
 */
struct DeclaringFunctionParameterData
{
    // The name of the parameter
    std::string name;
    // The type of the parameter (currently only pointer (array) and int32)
    llvm::Type *type;
};


class CodeGenerator
{
public:
    // Different types of arithmetic operators of the language
    enum class Operator { 
        PLUS = PLUS,
        MINUS = MINUS,
        MULT = TIMES,
        LESS_THAN = LSS,
        EQUALS = DOUBLE_EQ,
    };
private:
    // LLVM codegen variables
    std::unique_ptr<llvm::LLVMContext> the_context;
    std::unique_ptr<llvm::IRBuilder<llvm::NoFolder>> builder;
    std::unique_ptr<llvm::Module> the_module;

    // List of declared variables in current scope
    std::unordered_map<std::string, llvm::Value *> local_variables;

    // A list of operators which should be applied to values in semantic stack later
    std::vector<CodeGenerator::Operator> operator_stack;
    // Each variable or function is either int or void
    enum class VariableType {
        VOID,
        INT,
    };
    // Types which can be pushed in the semantic stack
    typedef std::variant<llvm::Value *, CodeGenerator::VariableType, int> SemanticStaticObject;
    // The good old semantic stack
    std::vector<SemanticStaticObject> semantic_stack;
    // Name of the variable/function we are declaring
    std::string declaring_pid_name, declaring_function_name;
    // The list of parameters of this function which we are currently declaring.
    std::vector<DeclaringFunctionParameterData> declaring_function_params;
    // True if we are in global scope, otherwise false.
    bool in_global_scope;

    // Function calls
    void generate_prelude();
    llvm::Value *deference_ptr_if_needed(llvm::Value *);
public:

    // Function calls
    explicit CodeGenerator();
    void print_code();
    void void_type();
    void int_type();
    void declaring_pid(const char *);
    void variable_declared();
    void array_declared();
    void function_start();
    void array_param();
    void int_param();
    void function_params_end();
    void function_end();
    void pid(const char *);
    void immediate(int);
    void pop_expression();
    void assign();
    void array();
    void immediate_val(int);
    void save_operator(CodeGenerator::Operator);
    void negate();
    void calculate();
};
