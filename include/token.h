#ifndef TOKEN_H
#define TOKEN_H

// Return tokens [0-255] for unknown characters, else ireturn one of these for known things
enum Token {
  // End Of File
  tok_eof = -1,

  // Commands
  tok_def = -2,
  tok_extern = -3,

  // Primary
  tok_identifier = -4,
  tok_number = -5,
  tok_string = -6,

  // My Personal Edit on Start End and Comment :3
  tok_comment = -7,
  tok_beginInc = -8,
  tok_endInc = -9,
  tok_beginBody = -10,
  tok_endBody = -11,

  // control
  tok_if = -12,
  tok_else = -13,
  tok_for = -14,
  tok_in = -15,

  // operators
  tok_binary = -16,
  tok_unary = -17,
  
  // var definition
  tok_var = -18,

  // punctuation
  tok_lparen = '(',  // (
  tok_rparen = ')',  // )
  tok_lbrace = '{',  // {
  tok_rbrace = '}',  // }
  tok_semi   = ';',  // ;

};

#endif // TOKEN_H