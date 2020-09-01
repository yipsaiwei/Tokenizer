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



typedef struct Tokenizer Tokenizer;
struct Tokenizer {
  char *str;
  int index;
  //uint32_t prevStartColumn;
  uint32_t length;
  //int tokenIndex;
  DoubleLinkedList *list;
};


Tokenizer *createTokenizer(char *str);
void  freeTokenizer(Tokenizer *tokenizer);
Token *getToken(Tokenizer *tokenizer);
Token *getNextToken(Tokenizer *tokenizer);
void  freeToken(void *token);
Token *createToken(Tokenizer *tokenizer);
Token *getIntegerOrFloatToken(Tokenizer *tokenizer);
TOKENTYPE getNumberType(char  *str);
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
#endif // TOKENIZER_H
