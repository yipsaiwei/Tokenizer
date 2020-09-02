#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "Token.h"
#include <stdint.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include  "Errors.h"
#include  "DoubleLinkedList.h"
#include  "MemAlloc.h"

#define TOKENIZER_DOLLAR_SIGN_HEX         (1 << 0)
#define TOKENIZER_HEX_H                   (1 << 1)
#define TOKENIZER_OCT_O                   (1 << 2)
#define TOKENIZER_BIN_B                   (1 << 3)

typedef struct Tokenizer Tokenizer;
struct Tokenizer {
  char *str;
  int index;
  uint32_t  config;
  uint32_t length;
  DoubleLinkedList *list;
};


Tokenizer *createTokenizer(char *str);
void  freeTokenizer(Tokenizer *tokenizer);
Token *getToken(Tokenizer *tokenizer);
void  freeToken(void *token);
Token *createToken(Tokenizer *tokenizer);
Token *getIntegerOrFloatToken(Tokenizer *tokenizer);
char *tokenizerSkipSpaces(Tokenizer *tokenizer);
TokenInteger *getOctalToken(Tokenizer  *tokenizer);
TokenInteger *getHexToken(Tokenizer *tokenizer);
TokenFloat *getFloatToken(Tokenizer  *tokenizer);
TokenInteger *getBinToken(Tokenizer  *tokenizer);
TokenInteger *getDecimalToken(Tokenizer  *tokenizer);
Token  *getNumberToken(Tokenizer *tokenizer);
TokenIdentifier *getIdentifierToken(Tokenizer *tokenizer);
TokenOperator *getOperatorToken(Tokenizer *tokenizer);
TokenString  *getStringToken(Tokenizer  *tokenizer);
char  *duplicateSubstring(char *str, int length);
char  *errorIndicator(int startColumn, char *str);
void  callThrowException(char *message, char *str, int startColumn, int errorType);
void  pushBackToken(Tokenizer *tokenizer, Token *token);
Token *popToken(Tokenizer *tokenizer);
Token *duplicateToken(Token  *token);
void configureTokenizer(Tokenizer *tokenizer, uint32_t configuration);
#endif // TOKENIZER_H
