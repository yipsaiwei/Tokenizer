#include "Tokenizer.h"
#include "Exception.h"
#include "CException.h"

Tokenizer *createTokenizer(char *str){
  Tokenizer *tokenizer;
  tokenizer = malloc(sizeof(Tokenizer));
  tokenizer->index = 0;
  tokenizer->length = strlen(str);
  tokenizer->str = str;
  // Will detect type of token here
  return  tokenizer;
}

void  freeTokenizer(Tokenizer *tokenizer){
  free(tokenizer);
}

token *getToken(Tokenizer *tokenizer){
  token *newToken = createToken(tokenizer);
  int i;
  newToken->type = checkTokenType(newToken);
  newToken->length = strlen(newToken->str);
  tokenizer->index += newToken->length;
  return  newToken;
}
  
token *createToken(Tokenizer  *tokenizer){
  token *newToken = malloc(sizeof(token));
  newToken->originalstr = tokenizer->str;
  newToken->startColumn = tokenizer->index;
  return newToken;
}

void  freeToken(token *Token){
  free(Token);
}

char  *skipWhiteSpaces(char *str){
  while(isspace(*str)){
    str++;
  }
  return  str;
}

tokenType checkTokenType(token  *newToken){
  char  *str = newToken->originalstr;
  tokenType  type;
  for(int a = 0; a < newToken->startColumn; a++)
    str++;
  if(isspace(*str))
    str = skipWhiteSpaces(str);
  if(isalpha(*str)){
    newToken->str = checkIdentifier(str);
    return  IDENTIFIER_TYPE;
  }
  else  //if(isdigit(*str)){
    {
    newToken->str = checkInteger(newToken);
  }
}


char *checkIdentifier(char  *str){
  int i;
  char  *tokenstr;
  tokenstr = malloc(sizeof(char));
  while(isalnum(str[i])){
    i++;
  }
  strncpy(tokenstr, str,i);
  return  tokenstr;
}


char  *checkInteger(token *Token){
  int i = 0;
  char  *str = Token->originalstr;
  char  *resultstr;
  while(str[i]!=NULL && str[i]!=' '){
    if(isalpha(str[i]))
      throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid integer: %s", *str);
    if(str[i]=='.'){
      resultstr = checkFloat(str);
      Token->type = FLOAT_TYPE;
      return  resultstr;
    }
    i++;
  }
}



char  *checkFloat(char  *str){
  int j = 0;
  char  *resultstr;
  resultstr = malloc(sizeof(char));

  while(str[j] != '.'){
    j++;
  }
  j++;
  while(str[j]!=NULL &&str[j]!=' '){
    if(str[j]=='.')
      throwException(ERROR_INVALID_FLOAT,NULL, 0, "Multiple decimal points detected: %s", *str);
    if(!isdigit(str[j])){
      if(str[j]!='e'){
        throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid float: %s", *str);
      }
    }
    if(str[j] == 'e'){
      if(str[j+1] == '+' ||str[j+1] == '-'){
        if(str[j+2] == '+' || str[j+2] == '-')
          throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid float (exponential): %s", *str);
      }
    }
    j++;
  }
 strncpy(resultstr, str, j);
 return resultstr;
  
}
