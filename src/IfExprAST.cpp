#include "../include/IfExprAST.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"

llvm::Value *IfExprAST::codegen() {
    llvm::Value *condV = Cond->codegen();
    if (!condV) return nullptr;

    condV = Builder->CreateFCmpONE(
        condV, llvm::ConstantFP::get(*TheContext, llvm::APFloat(0.0)), "ifcond"
    );

    llvm::Function *F = Builder->GetInsertBlock()->getParent();

    llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(*TheContext, "then", F);
    llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(*TheContext, "else");
    llvm::BasicBlock *MergeBB = llvm::BasicBlock::Create(*TheContext, "ifcont");

    Builder->CreateCondBr(condV, ThenBB, ElseBB);

    // ---- THEN ----
    Builder->SetInsertPoint(ThenBB);
    llvm::Value *ThenV = Then->codegen();
    Builder->CreateBr(MergeBB);
    ThenBB = Builder->GetInsertBlock();

    // ---- ELSE ----
    F->insert(F->end(), ElseBB);
    Builder->SetInsertPoint(ElseBB);

    llvm::Value *ElseV;
    if (Else)
        ElseV = Else->codegen();
    else
        ElseV = llvm::ConstantFP::get(*TheContext, llvm::APFloat(0.0));

    Builder->CreateBr(MergeBB);
    ElseBB = Builder->GetInsertBlock();

    // ---- MERGE ----
    F->insert(F->end(), MergeBB);
    Builder->SetInsertPoint(MergeBB);

    llvm::PHINode *PN = Builder->CreatePHI(
        llvm::Type::getDoubleTy(*TheContext), 2, "iftmp"
    );
    PN->addIncoming(ThenV, ThenBB);
    PN->addIncoming(ElseV, ElseBB);

    return PN;
}
