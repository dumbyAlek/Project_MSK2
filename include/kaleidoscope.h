#ifndef KALEIDOSCOPE_H
#define KALEIDOSCOPE_H

#include <map>
#include <memory>
#include <string>
#include "llvm_all.h"

// This is an object that owns LLVM core data structures
extern std::unique_ptr<llvm::LLVMContext> TheContext;
// This is a helper object that makes easy to generate LLVM instructions
extern std::unique_ptr<llvm::IRBuilder<>> Builder;
// This is an LLVM construct that contains functions and global variables
extern std::unique_ptr<llvm::Module> TheModule;
// This map keeps track of which values are defined in the current scope
extern std::map<std::string, llvm::Value *> NamedValues;

#endif // KALEIDOSCOPE_H