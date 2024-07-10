#include "codegen.hpp"

CodeGenerator::CodeGenerator(yyscan_t scanner) : the_context(std::make_unique<llvm::LLVMContext>()),
                                                          the_module(std::make_unique<llvm::Module>("my cool jit", *the_context)),
                                                          builder(std::make_unique<llvm::IRBuilder<>>(*the_context)),
                                                          scanner(scanner)
{
}

void CodeGenerator::void_type() {
    this->semantic_stack.push_back(VariableType::VOID);
}

void CodeGenerator::int_type() {
    this->semantic_stack.push_back(VariableType::INT);
}