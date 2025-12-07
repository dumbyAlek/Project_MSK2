#include "../include/BlockAST.h"

llvm::Value *BlockAST::codegen() {
    llvm::Value *last = nullptr;

    for (auto &stmt : Statements) {
        last = stmt->codegen();
        if (!last)
            return nullptr;
    }
    return last;  // result of the block
}
