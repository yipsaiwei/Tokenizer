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
  int lineNum;
  DoubleLinkedList *list;
};


Tokenizer *createTokenizer(char *str);
void  freeTokenizer(Tokenizer *tokenizer);
Token *getToken(Tokenizer *tokenizer);
char *skipWhiteSpaces(char  *str);
char *tokenizerSkipSpaces(Tokenizer *tokenizer);
IntegerToken *getOctalToken(Tokenizer  *tokenizer);
IntegerToken *getHexToken(Tokenizer *tokenizer);
FloatToken *getFloatToken(Tokenizer  *tokenizer);
IntegerToken *getBinToken(Tokenizer  *tokenizer);
IntegerToken *getDecimalToken(Tokenizer  *tokenizer);
Token  *getNumberToken(Tokenizer *tokenizer);
IdentifierToken *getIdentifierToken(Tokenizer *tokenizer);
OperatorToken *getOperatorToken(Tokenizer *tokenizer);
StringToken  *getStringToken(Tokenizer  *tokenizer);
Token *getNewlineToken(Tokenizer  *tokenizer);
char  *duplicateSubstring(char *str, int length);
char  *errorIndicator(int startColumn, char *str);
void  callThrowException(char *message, char *str, int startColumn, int errorType);
void  pushBackToken(Tokenizer *tokenizer, Token *token);
Token *popToken(Tokenizer *tokenizer);
void configureTokenizer(Tokenizer *tokenizer, uint32_t configuration);
#endif // TOKENIZER_H
