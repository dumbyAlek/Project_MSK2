#ifndef EXPR_AST_H
#define EXPR_AST_H

#include "llvm_all.h"

class ExprAST {
public:
  virtual ~ExprAST() = default;
  virtual llvm::Value *codegen() = 0;
};

#endif // EXPR_AST_H