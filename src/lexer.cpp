#include "../include/lexer.h"


using namespace std;

int CurrentToken;
string IdentifierStr;
double NumVal;
string StringVal;

// Gets one character at a time using getchar() and store in LastChar
int gettok() {
  static int LastChar = ' ';

  // Ignore Whitespaces between Tokens
  while (isspace(LastChar)) {
    LastChar = getchar();
  }

  // Custom .SOMETHING. format implementation
  if (LastChar == '.') {
    string DirStr = ".";
    LastChar = getchar();

    // Keep reading letters, digits, or dots
    while (LastChar != EOF && LastChar != '.') {
        DirStr += LastChar;
        LastChar = getchar();
    }
    if(LastChar == '.'){
        DirStr += LastChar;
        LastChar = getchar();  
    }

    // Map known directives to tokens
    // Start Comment with ".apnader_ektu_somoy_nosto_kori.", the whole line is commented out
    if (DirStr == ".Apnader_ektu_somoy_nosto_kori.") {

        // skip until end of line
        while (LastChar != '\n' && LastChar != '\r' && LastChar != EOF) {
            LastChar = getchar();
        }
        return gettok(); 
    }

    if (DirStr == ".Dorja_bondho_koren.")  return tok_beginInc;
    if (DirStr == ".Toh_apnara_kew_bashay_poren_ni.")   return tok_endInc;
    if (DirStr == ".Ashen_poraLekha_kori.")  return tok_beginBody;
    if (DirStr == ".fr_fr_noCap.")   return tok_endBody;

    // Unknown directive: treat as identifier
    IdentifierStr = DirStr;
    return tok_identifier;
  }

  // Recognize Identifier and Specific Keywords
  // isalpha(char) returns True if the char is an alphabet, else return False
  if (isalpha(LastChar)) {
    IdentifierStr = LastChar;

    // Stacking together all alphanumeric characters into IdentifierStr
    // isalnum(char) returns True if the char is an alphanumeric, else return False
    while (isalnum(LastChar = getchar())) {
      IdentifierStr += LastChar; // Append
    }

    if (IdentifierStr == "def") {
      return tok_def;
    }

    if (IdentifierStr == "extern") {
      return tok_extern;
    }

    if (IdentifierStr == "if"){
      return tok_if;
    }
      
    if (IdentifierStr == "else"){
      return tok_else;
    }


    return tok_identifier;
  }

  // Stacking together only numeric values
  // isdigit(char) returns True if the char is a digit, else return False
  if (isdigit(LastChar) || LastChar == '.') {
    string NumStr;

    do {
      NumStr += LastChar; // Append
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    // Numeric String --> Numeric Value saved in NumVal
    // strtod --> string to double 
    NumVal = strtod(NumStr.c_str(), 0);
    return tok_number;
  }

  if (LastChar == '"') {
    string StrVal;
    while (true) {
        LastChar = getchar();
        if (LastChar == '"' || LastChar == EOF) break; // end of string
        StrVal += LastChar;
    }
    LastChar = getchar(); // consume closing quote
    // store string somewhere global
    StringVal = StrVal;
    return tok_string;
  }

  // It NONE of the Cases work, its either end of file or operator
  if (LastChar == EOF) {
    return tok_eof;
  }

  // single-character tokens
  switch (LastChar) {
      case '(': LastChar = getchar(); return tok_lparen;
      case ')': LastChar = getchar(); return tok_rparen;
      case '{': LastChar = getchar(); return tok_lbrace;
      case '}': LastChar = getchar(); return tok_rbrace;
      case ';': LastChar = getchar(); return tok_semi;
  }

  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
}

int getNextToken() {
  return CurrentToken = gettok();
}

// Note to self: the getchar() is getting the characters from the input stram as we run it