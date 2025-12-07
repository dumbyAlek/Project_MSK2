#include "../include/headers.h" 
#include "../include/llvm_all.h"
#include "../include/codeGen.h"

using namespace llvm;
using namespace llvm::orc;

std::map<std::string, std::unique_ptr<PrototypeAST>> FunctionProtos;

Function *getFunction(std::string Name) {
  // First, see if the function already exists in the module.
  if (auto *F = TheModule->getFunction(Name))
    return F;

  // Otherwise check if we have a prototype.
  auto FI = FunctionProtos.find(Name);
  if (FI != FunctionProtos.end())
    return FI->second->codegen();

  return nullptr;
}
