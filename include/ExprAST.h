#ifndef EXPR_AST_H
#define EXPR_AST_H

namespace llvm {
    class Value;
}

class ExprAST {
public:
  virtual ~ExprAST() = default;
  virtual llvm::Value *codegen() = 0;
};

#endif // EXPR_AST_H