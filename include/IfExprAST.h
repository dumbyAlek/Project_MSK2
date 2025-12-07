#pragma once
#include <memory>
#include "ExprAST.h"
#include "kaleidoscope.h"

class IfExprAST : public ExprAST {
    std::unique_ptr<ExprAST> Cond;
    std::unique_ptr<ExprAST> Then;
    std::unique_ptr<ExprAST> Else;

public:
    IfExprAST(std::unique_ptr<ExprAST> Cond,
              std::unique_ptr<ExprAST> Then,
              std::unique_ptr<ExprAST> Else)
        : Cond(std::move(Cond)),
          Then(std::move(Then)),
          Else(std::move(Else)) {}

    llvm::Value *codegen() override;
};
