#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "Token.h"
#include <stdint.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

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
token *createToken(char *tokenstr);
#endif // TOKENIZER_H
