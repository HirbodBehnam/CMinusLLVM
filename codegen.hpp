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
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <memory>
#include <string>
#include <variant>
#include <vector>
#include <unordered_map>

class CodeGenerator
{
private:
    // LLVM codegen variables
    std::unique_ptr<llvm::LLVMContext> the_context;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    std::unique_ptr<llvm::Module> the_module;
    std::unordered_map<std::string, llvm::Value *> global_variables;
    yyscan_t scanner;

    // Different types of operators of the language
    enum class Operator { 
        PLUS,
        MINUS,
        MULT,
        LESS_THAN,
        EQUALS,
    };
    std::vector<CodeGenerator::Operator> operator_stack;
    // Each variable or function is either int or void
    enum class VariableType {
        VOID,
        INT,
    };
    // Types which can be pushed in the semantic stack
    typedef std::variant<llvm::Value *, CodeGenerator::VariableType> SemanticStaticObject;
    // The good old semantic stack
    std::vector<SemanticStaticObject> semantic_stack;
    // Name of the variable we are declaring
    std::string declaring_pid_name;
    // True if we are in global scope, otherwise false.
    bool in_global_scope;

    // Function calls
    void generate_prelude();
public:
    // Function calls
    explicit CodeGenerator(yyscan_t scanner);
    void print_code();
    void void_type();
    void int_type();
    void declaring_pid(const char *);
    void variable_declared();
    void array_declared();
};
