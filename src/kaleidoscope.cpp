#include "../include/kaleidoscope.h"


// This is an object that owns LLVM core data structures
std::unique_ptr<llvm::LLVMContext> TheContext;

// This is a helper object that makes easy to generate LLVM instructions
// Builder and Module are constructed later in InitializeModuleAndManagers()
std::unique_ptr<llvm::IRBuilder<>> Builder;
std::unique_ptr<llvm::Module> TheModule;

// This map keeps track of which values are defined in the current scope
std::map<std::string, llvm::Value *> NamedValues;

// Optional convenience accessor (useful if you prefer value-style calls)
llvm::IRBuilder<> &TheBuilder() {
  // runtime assert helpful for debugging
  assert(Builder && "Builder used before initialization");
  return *Builder;
}