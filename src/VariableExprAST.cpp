#include "../include/VariableExprAST.h"
#include "../include/logger.h"
#include "../include/kaleidoscope.h"

llvm::Value *VariableExprAST::codegen() {
  llvm::Value *V = NamedValues[Name];

  if (!V) {
    LogErrorV("Unknown variable name");
    return nullptr;
  }

  return V;
}