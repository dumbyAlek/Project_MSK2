#pragma once
#include <memory>
#include <vector>
#include "ExprAST.h"
#include "kaleidoscope.h"

class BlockAST : public ExprAST {
    std::vector<std::unique_ptr<ExprAST>> Statements;

public:
    BlockAST(std::vector<std::unique_ptr<ExprAST>> Stmts)
        : Statements(std::move(Stmts)) {}

    llvm::Value *codegen() override;
};
