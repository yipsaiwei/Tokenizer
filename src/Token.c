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
  Token *tokenFree, *tokenptr;
  tokenFree = (Token  *)token;
  if(tokenFree){
    tokenptr = tokenFree;
    tokenFree = NULL;
  if(tokenptr->str)
    memFree(tokenptr->str);
  memFree(tokenptr);
  }
}

void tokenExpandString(Token  *token, int lengthToExpand){
  memFree(token->str);
  token->str = duplicateSubstring((token->originalstr + token->startColumn), lengthToExpand + 1);
}

Token *cloneToken(Token *token){
  char  *originalStr = token->originalstr;
  char  *str = strdup(token->str);
  if(token->type == TOKEN_OPERATOR_TYPE)
    return  (Token  *)createOperatorToken(str, token->startColumn, originalStr, token->type);
  else if(token->type == TOKEN_INTEGER_TYPE)
    return  (Token  *)createIntToken( ((IntegerToken  *)token)->value, token->startColumn, originalStr, str, token->type);
  else if(token->type == TOKEN_FLOAT_TYPE)
    return  (Token  *)createFloatToken( ((FloatToken  *)token)->value, token->startColumn, originalStr, str, token->type);
  else 
    return  (Token  *)createStringToken(str, token->startColumn, originalStr, token->type);
}

void dumpTokenErrorMessage(CEXCEPTION_T ex, int lineNo){
  int column = 0;
  Token *token = ex->data;
  if(ex->data == NULL){
    printf("Error on line %d:%d: %s\n ", lineNo, column, ex->msg);
  }else{
    char  *errorLine = errorIndicator(token->startColumn, token->length);
    printf("Error on line %d:%d: %s\n%s\n%s\n", lineNo, token->startColumn, ex->msg, token->originalstr, errorLine);
    memFree(errorLine);
    freeToken(token);
  }
}

