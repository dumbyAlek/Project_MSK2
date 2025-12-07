#ifndef CALL_EXPR_AST_H
#define CALL_EXPR_AST_H

#include "ExprAST.h"
#include <string>
#include <vector>
#include <memory>
#include "llvm_all.h"

#include "logger.h"
#include "kaleidoscope.h"

using namespace std;

// Expression class for function calls
class CallExprAST : public ExprAST {
  string Callee;
  vector<unique_ptr<ExprAST>> Args;

public:
  CallExprAST(const string &Callee, vector<unique_ptr<ExprAST>> Args)
   : Callee(Callee), Args(move(Args)) {}
  llvm::Value *codegen() override;
};

#endif // CALL_EXPR_AST_H