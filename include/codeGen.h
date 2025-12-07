#ifndef CODEGEN_H
#define CODEGEN_H

#include <string>
#include <map>
#include <memory>
#include "llvm/IR/Function.h"
#include "PrototypeAST.h"

// Declare externs so they exist only once
extern std::map<std::string, std::unique_ptr<PrototypeAST>> FunctionProtos;
llvm::Function *getFunction(const std::string &Name);

#endif
