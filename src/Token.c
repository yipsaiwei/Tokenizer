#include "Token.h"
#include "Exception.h"
#include "CException.h"
#include  "Tokenizer.h"


TokenInteger *createIntToken(int  value, int  index, char  *originalstr, char *str, TOKENTYPE  type){
  TokenInteger *newToken = malloc(sizeof(TokenInteger));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  newToken->length = strlen(str);
  newToken->value = value;
  return newToken;
}

TokenFloat *createFloatToken(double  value, int  index, char  *originalstr, char  *str, TOKENTYPE  type){
  TokenFloat *newToken = malloc(sizeof(TokenFloat));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  newToken->value = value;
  return newToken;
}

TokenIdentifier *createIdentifierToken(char *str, int  index, char  *originalstr, TOKENTYPE  type){
  TokenIdentifier *newToken = malloc(sizeof(TokenIdentifier));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  return newToken;
}

TokenString *createStringToken(char *str, int  index, char  *originalstr, TOKENTYPE  type){
  TokenString *newToken = malloc(sizeof(TokenString));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  return newToken;
}

TokenOperator *createOperatorToken(char *str, int  index, char  *originalstr, TOKENTYPE  type){
  TokenOperator *newToken = malloc(sizeof(TokenOperator));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  return newToken;
}

