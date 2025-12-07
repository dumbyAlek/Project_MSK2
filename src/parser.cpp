#include "../include/parser.h"

std::map<char, int> BinopPrecedence;

static int GetTokPrecedence() {
  if (!isascii(CurrentToken)) {
    return -1;
  }

  int TokPrec = BinopPrecedence[CurrentToken];
  if (TokPrec <= 0) return -1;

  return TokPrec;
}

// This routine expects to be called when the current token is a tok_number
// It takes the current number value and creates a NumberExprAST node
std::unique_ptr<ExprAST> ParseNumberExpr() {
  auto Result = std::make_unique<NumberExprAST>(NumVal);
  getNextToken();
  return std::move(Result);
}

// This routine parses expressions in "(" and ")" characters
std::unique_ptr<ExprAST> ParseParenExpr() {
  getNextToken();

  auto V = ParseExpression();
  if (!V) {
    return nullptr;
  }

  if (CurrentToken != ')') {
    return LogError("Expected )");
  }

  getNextToken();
  return V;
}

// This routine expects to be called when current token is tok_identifier
std::unique_ptr<ExprAST> ParseIdentifierExpr() {
  std::string IdName = IdentifierStr;

  getNextToken();

  if (CurrentToken != '(') {
    return std::make_unique<VariableExprAST>(IdName);
  }

  getNextToken();
  std::vector<std::unique_ptr<ExprAST>> Args;
  if (CurrentToken != ')') {
    while (true) {
      if (auto Arg = ParseExpression()) {
        Args.push_back(std::move(Arg));
      } else {
        return nullptr;
      }

      if (CurrentToken == ')') {
        break;
      }

      if (CurrentToken != ',') {
        return LogError("Expected ')' or ',' in argument list");
      }

      getNextToken();
    }
  }

  getNextToken();

  return std::make_unique<CallExprAST>(IdName, std::move(Args));
}

std::unique_ptr<ExprAST> ParsePrimary() {
    switch (CurrentToken) {
        case tok_identifier:
            return ParseIdentifierExpr();
        case tok_number:
            return ParseNumberExpr();
        case '(':
            return ParseParenExpr();
        case tok_lbrace:
            return ParseBlock();
        default:
            // Check if it is an operator (for binary ops)
            if (isprint(CurrentToken)) {
                int Op = CurrentToken;
                getNextToken();
                return std::make_unique<VariableExprAST>(std::string(1, (char)Op));
            }
            return LogError("Unknown token when expecting an expression");
    }
}


std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS) {
  while (true) {
    int TokPrec = GetTokPrecedence();

    if (TokPrec < ExprPrec) {
      return LHS;
    }

    int BinOp = CurrentToken;
    getNextToken();

    auto RHS = ParsePrimary();
    if (!RHS) {
      return nullptr;
    }

    int NextPrec = GetTokPrecedence();
    if (TokPrec < NextPrec) {
      RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
      if (!RHS) {
        return nullptr;
      }
    }

    LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
  }
}

std::unique_ptr<ExprAST> ParseExpression() {
  auto LHS = ParsePrimary();

  if (!LHS) {
    return nullptr;
  }

  return ParseBinOpRHS(0, std::move(LHS));
}

std::unique_ptr<PrototypeAST> ParsePrototype() {
  if (CurrentToken != tok_identifier) {
    return LogErrorP("Expected function name in prototype");
  }

  std::string FnName = IdentifierStr;
  getNextToken();

  if (CurrentToken != '(') {
    return LogErrorP("Expected '(' in prototype");
  }
  
  getNextToken(); // eat '('

    std::vector<std::string> ArgNames;

    if (CurrentToken != ')') { // check if there are arguments
        while (true) {
            if (CurrentToken != tok_identifier)
                return LogErrorP("Expected argument name");

            ArgNames.push_back(IdentifierStr);
            getNextToken(); // eat identifier

            if (CurrentToken == ')') // end of argument list
                break;

            if (CurrentToken != ',') // expecting comma between args
                return LogErrorP("Expected ',' between arguments");

            getNextToken(); // eat comma
        }
    }

  getNextToken(); // eat ')'

  return std::make_unique<PrototypeAST>(FnName, std::move(ArgNames));
}

std::unique_ptr<FunctionAST> ParseDefinition() {
  getNextToken();

  auto Proto = ParsePrototype();
  if (!Proto) {
    return nullptr;
  }

  if (auto E = ParseExpression()) {
    return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
  }

  return nullptr;
}

std::unique_ptr<FunctionAST> ParseTopLevelExpr() {
  if (auto E = ParseExpression()) {
    auto Proto = std::make_unique<PrototypeAST>("__anon_expr", std::vector<std::string>());
    return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
  }

  return nullptr;
}

std::unique_ptr<PrototypeAST> ParseExtern() {
  getNextToken();
  return ParsePrototype();
}

std::unique_ptr<BlockAST> ParseBlock() {
    if (CurrentToken != tok_lbrace)
        return LogErrorB("expected '{'");

    getNextToken(); // eat '{'
    std::vector<std::unique_ptr<ExprAST>> Statements;

    while (CurrentToken != tok_rbrace && CurrentToken != tok_eof) {
        auto Stmt = ParseStatement();
        if (!Stmt) return nullptr;
        Statements.push_back(std::move(Stmt));
    }

    if (CurrentToken != tok_rbrace)
        return LogErrorB("expected '}'");
    getNextToken(); // eat '}'

    return std::make_unique<BlockAST>(std::move(Statements));
}

std::unique_ptr<ExprAST> ParseStatement() {
    switch (CurrentToken) {
        case tok_if:
            return ParseIfStmt();
        default:
            auto Expr = ParseExpression();
            if (!Expr) return nullptr;
            if (CurrentToken == tok_semi) getNextToken(); // optional ';'
            return Expr;
    }
}

std::unique_ptr<ExprAST> ParseIfStmt() {
    getNextToken(); // eat 'if'

    if (CurrentToken != tok_lparen)
        return LogError("expected '(' after 'if'");
    getNextToken(); // eat '('

    auto Cond = ParseExpression();
    if (!Cond)
        return nullptr;

    if (CurrentToken != tok_rparen)
        return LogError("expected ')'");
    getNextToken(); // eat ')'

    // enforce C-style block
    if (CurrentToken != tok_lbrace)
        return LogError("expected '{' after if(...)");
    auto Then = ParseBlock();
    if (!Then)
        return nullptr;

    std::unique_ptr<BlockAST> Else = nullptr;

    if (CurrentToken == tok_else) {
        getNextToken(); // eat 'else'

        if (CurrentToken != tok_lbrace)
            return LogError("expected '{' after else");
        Else = ParseBlock();
        if (!Else)
            return nullptr;
    }

    return std::make_unique<IfExprAST>(
        std::move(Cond),
        std::move(Then),
        std::move(Else)
    );
}

