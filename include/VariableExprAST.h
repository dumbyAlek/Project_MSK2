#ifndef VARIABLE_EXPR_AST_H
#define VARIABLE_EXPR_AST_H

#include "ExprAST.h"
#include <string>

// Expression class for referencing a variable, like "a"
class VariableExprAST : public ExprAST {
  std::string Name;

public:
  VariableExprAST(const std::string &Name) : Name(Name) {}
  llvm::Value *codegen() override;
};

#endif // VARIABLE_EXPR_AST_H