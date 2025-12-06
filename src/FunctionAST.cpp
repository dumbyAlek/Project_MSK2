#include "../include/FunctionAST.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Verifier.h"
#include "../include/kaleidoscope.h"

// Generates LLVM code for functions declarations
llvm::Function *FunctionAST::codegen() {
  llvm::Function *TheFunction = TheModule->getFunction(Proto->getName());

  if (!TheFunction) {
    TheFunction = Proto->codegen();
  }

  if (!TheFunction) {
    return nullptr;
  }

  llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", TheFunction);
  Builder.SetInsertPoint(BB);
  NamedValues.clear();
  for (auto &Arg : TheFunction->args()) {
    NamedValues[Arg.getName().data()] = &Arg;
  }

  if (llvm::Value *RetVal = Body->codegen()) {
    Builder.CreateRet(RetVal);
    verifyFunction(*TheFunction);

    return TheFunction;
  }

  TheFunction->eraseFromParent();
  return nullptr;
}