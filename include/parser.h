#ifndef PARSER_H
#define PARSER_H

#include <map>
#include "BinaryExprAST.h"
#include "CallExprAST.h"
#include "ExprAST.h"
#include "FunctionAST.h"
#include "NumberExprAST.h"
#include "PrototypeAST.h"
#include "VariableExprAST.h"
#include "BlockAST.h"
#include "IfExprAST.h"
#include "lexer.h"
#include "token.h"
#include "logger.h"
#include "llvm_all.h"

using namespace std;

extern map<char, int> BinopPrecedence;
unique_ptr<ExprAST> ParseNumberExpr();
unique_ptr<ExprAST> ParseParenExpr();
unique_ptr<ExprAST> ParseIdentifierExpr();
unique_ptr<ExprAST> ParsePrimary();
unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, unique_ptr<ExprAST> LHS);
unique_ptr<ExprAST> ParseExpression();
unique_ptr<PrototypeAST> ParsePrototype();
unique_ptr<FunctionAST> ParseDefinition();
unique_ptr<FunctionAST> ParseTopLevelExpr();
unique_ptr<PrototypeAST> ParseExtern();
unique_ptr<BlockAST> ParseBlock();
unique_ptr<ExprAST> ParseStatement();
unique_ptr<ExprAST> ParseIfStmt();

#endif // PARSER_H