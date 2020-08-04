#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "Token.h"
#include <stdint.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct Tokenizer Tokenizer;
struct Tokenizer {
  char *str;
  int index;
  uint32_t length;
  token *token[10];
};

Tokenizer *createTokenizer(char *str);
void  freeTokenizer(Tokenizer *tokenizer);
token *getToken(Tokenizer *tokenizer);
void  freeToken(token *Token);
token *createToken(Tokenizer *tokenizer);
char  *skipWhiteSpaces(char *str);
char *checkIdentifier(char  *str);
char  *checkInteger(token *Token);
char  *checkFloat(char  *str);
#endif // TOKENIZER_H
