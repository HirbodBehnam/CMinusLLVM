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

    // Variables for the code generator itself

public:
    explicit CodeGenerator(yyscan_t scanner);
};
