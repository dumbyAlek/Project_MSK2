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
};

#endif // TOKEN_H