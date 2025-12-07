#ifndef BINARY_EXPR_AST_H
#define BINARY_EXPR_AST_H

#include <memory>
#include "ExprAST.h"
#include "llvm_all.h"
#include "kaleidoscope.h"
#include "logger.h"

using namespace std;

// Expression class for a binary operator
class BinaryExprAST : public ExprAST {
  char Op;
  unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryExprAST(char op, unique_ptr<ExprAST> LHS, unique_ptr<ExprAST> RHS)
   : Op(op), LHS(move(LHS)), RHS(move(RHS)) {}
  llvm::Value *codegen() override;
};

#endif