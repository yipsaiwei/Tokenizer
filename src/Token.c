#include "Token.h"
#include "Exception.h"
#include "CException.h"
#include  "Tokenizer.h"


IntegerToken *createIntToken(int  value, int  index, char  *originalstr, char *str, TOKENTYPE  type){
  IntegerToken *newToken = memAlloc(sizeof(IntegerToken));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  newToken->length = strlen(str);
  newToken->value = value;
  return newToken;
}

FloatToken *createFloatToken(double  value, int  index, char  *originalstr, char  *str, TOKENTYPE  type){
  FloatToken *newToken = memAlloc(sizeof(FloatToken));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  newToken->length = strlen(str);
  newToken->value = value;
  return newToken;
}

IdentifierToken *createIdentifierToken(char *str, int  index, char  *originalstr, TOKENTYPE  type){
  IdentifierToken *newToken = memAlloc(sizeof(IdentifierToken));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  newToken->length = strlen(str);
  return newToken;
}

StringToken *createStringToken(char *str, int  index, char  *originalstr, TOKENTYPE  type){
  StringToken *newToken = memAlloc(sizeof(StringToken));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  newToken->length = strlen(str);
  return newToken;
}

OperatorToken *createOperatorToken(char *str, int  index, char  *originalstr, TOKENTYPE  type){
  OperatorToken *newToken = memAlloc(sizeof(OperatorToken));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->type = type;
  newToken->length = strlen(str);
  return newToken;
}


Token *createNULLToken(char *originalstr, int index, TOKENTYPE type){
  Token *newToken = memAlloc(sizeof(Token));
  newToken->originalstr = originalstr;
  newToken->str = NULL;
  newToken->startColumn = index;
  newToken->length = 0;
  newToken->type = type;
  return  newToken;
}

Token *createNewlineToken(char  *str, int index, char  *originalstr, TOKENTYPE type){
  Token *newToken = memAlloc(sizeof(Token));
  newToken->originalstr = originalstr;
  newToken->str = str;
  newToken->startColumn = index;
  newToken->length = strlen(str);
  newToken->type = type;
  return  newToken;
}

void  freeToken(void *token){
  Token *tokenFree;
  tokenFree = (Token  *)token;
  if(tokenFree->str)
    memFree(tokenFree->str);
  if(tokenFree)
    memFree(tokenFree);
}

void dumpTokenErrorMessage(CEXCEPTION_T ex, int lineNo){
  int column = 0;
  Token *token = NULL;
  token = ex->data;
  char  *errorLine = errorIndicator(token->startColumn, token->length);
  printf("Error on line %d:%d: %s : %s\n%s\n%s\n", lineNo, token->startColumn, ex->msg, token->str, token->originalstr, errorLine);
  freeToken(token);
  free(errorLine);
}

