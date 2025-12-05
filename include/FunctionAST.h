#ifndef FUNCTION_AST_H
#define FUNCTION_AST_H

#include "ExprAST.h"
#include "PrototypeAST.h"
#include <memory>

namespace llvm {
    class Function;
}

using namespace std;


// Represents a function definition itself
class FunctionAST {
  unique_ptr<PrototypeAST> Proto;
  unique_ptr<ExprAST> Body;

public:
  FunctionAST(unique_ptr<PrototypeAST> Proto, unique_ptr<ExprAST> Body) 
  : Proto(move(Proto)), Body(move(Body)) {}
  llvm::Function *codegen();
};

#endif // FUNCTION_AST_H