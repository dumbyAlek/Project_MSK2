#include "../include/NumberExprAST.h"
#include <llvm/IR/Constants.h>
#include "../include/kaleidoscope.h"

// Generate LLVM code for numeric literals
llvm::Value *NumberExprAST::codegen() {
  return llvm::ConstantFP::get(*TheContext, llvm::APFloat(Val));
}