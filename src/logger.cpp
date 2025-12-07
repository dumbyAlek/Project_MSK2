#include "../include/logger.h"

// ExprAST parser error
std::unique_ptr<ExprAST> LogError(const char *Str) {
  fprintf(stderr, "LogError: %s\n", Str);
  return nullptr;
}

// Prototype parser error
std::unique_ptr<PrototypeAST> LogErrorP(const char *Str) {
  LogError(Str);
  return nullptr;
}

// Block parser error
std::unique_ptr<BlockAST> LogErrorB(const char *Str) {
    fprintf(stderr, "Parse block error: %s\n", Str);
    return nullptr;
}

// LLVM codegen error
llvm::Value *LogErrorV(const char *Str) {
  LogError(Str);
  return nullptr;
}