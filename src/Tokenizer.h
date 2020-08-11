#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "Token.h"
#include <stdint.h>
#include <malloc.h>
#include <stdio.h>
#include  <stdlib.h>
#include <string.h>
#include <ctype.h>
#include  "Errors.h"


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
token *getNextToken(Tokenizer *tokenizer);
void  freeToken(token *Token);
token *createToken(Tokenizer *tokenizer);
int  getNumberToken(char  *str);
TOKENTYPE getIntegerOrFloatType(char  *str);
TOKENTYPE getNumberType(char  *str);
char *getIdentifier(char  *str);
char *getOperator(char  *str);
char *getString(char  *str);
TOKENTYPE checkTokenType(token  *newToken);
/*
char  *skipWhiteSpaces(char *str, int *i);
char *checkIdentifier(char  *str);
char  *checkInteger(token *Token);
char  *checkFloat(char  *str);
*/

int getOctalValue(char  *str);
int getHexValue(char  *str);
double getFloatValue(char  *str);
int getBinValue(char  *str);
int getDecimalValue(char  *str);
#endif // TOKENIZER_H
