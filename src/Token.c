#include "Token.h"
#include "Exception.h"
#include "CException.h"
#include  "Tokenizer.h"


TokenInteger *createIntToken(int  value, int  index, char  *originalstr, char *str, TOKENTYPE  type){
  TokenInteger *newToken = memAlloc(sizeof(TokenInteger));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  newToken->length = strlen(str);
  newToken->value = value;
  return newToken;
}

TokenFloat *createFloatToken(double  value, int  index, char  *originalstr, char  *str, TOKENTYPE  type){
  TokenFloat *newToken = memAlloc(sizeof(TokenFloat));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  newToken->length = strlen(str);
  newToken->value = value;
  return newToken;
}

TokenIdentifier *createIdentifierToken(char *str, int  index, char  *originalstr, TOKENTYPE  type){
  TokenIdentifier *newToken = memAlloc(sizeof(TokenIdentifier));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  newToken->length = strlen(str);
  return newToken;
}

TokenString *createStringToken(char *str, int  index, char  *originalstr, TOKENTYPE  type){
  TokenString *newToken = memAlloc(sizeof(TokenString));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  newToken->length = strlen(str);
  return newToken;
}

TokenOperator *createOperatorToken(char *str, int  index, char  *originalstr, TOKENTYPE  type){
  TokenOperator *newToken = memAlloc(sizeof(TokenOperator));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  newToken->length = strlen(str);
  return newToken;
}

