#include "Tokenizer.h"
#include "Exception.h"
#include "CException.h"
#include  "string.h"


Tokenizer  *createTokenizer(char *str){
  Tokenizer *tokenizer;
  tokenizer = malloc(sizeof(Tokenizer));
  tokenizer->index = 0;
  tokenizer->length = strlen(str);
  tokenizer->str = str;
  return  tokenizer;
}


void  freeTokenizer(Tokenizer *tokenizer){
  if(tokenizer != NULL)
    free(tokenizer);
}


Token  *getToken(Tokenizer *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  if  (isdigit(str[0]))
    return  getNumberToken(tokenizer);
  else  if(isalpha(str[0]) || str[0] == '_')
    return  getIdentifierToken(tokenizer);
  else  if(str[0] == '\"')
    return  getStringToken(tokenizer);
  else
    return  getOperatorToken(tokenizer);
}

 
Token  *createToken(Tokenizer  *tokenizer){
  Token *newToken = malloc(sizeof(Token));
  newToken->originalstr = tokenizer->str;
  newToken->startColumn = tokenizer->index;
  return newToken;
}


void  freeToken(void *token){
  Token *tokenFree;
  tokenFree = (Token  *)token;
  if(tokenFree->str != NULL)
    free( tokenFree->str);
  if(tokenFree != NULL)
    free(tokenFree);
}


char  *duplicateSubstring(char *str, int length){
  char  *resultstr = malloc((length+1)*sizeof(char));
  strncpy(resultstr, str, length);
  resultstr[length] = '\0';
  return  resultstr;
}

char *tokenizerSkipSpaces(Tokenizer *tokenizer){
  char  *str = tokenizer->str;
  for(int i = 0; i<tokenizer->index; i++)
    str++;
  while(isspace((tokenizer->str)[tokenizer->index] )){  
    (tokenizer->index) ++;
    str++;
  }
  return  str;
}


Token  *getNumberToken(Tokenizer *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  if(str[0] == '0'){
    if(isdigit(str[1]))
      return  getOctalToken(tokenizer);
    else if(str[1] == 'x')
      return  getHexToken(tokenizer);
    else if(str[1] == 'b')
      return  getBinToken(tokenizer);
    else
      return  getOctalToken(tokenizer);
  }
  else
    return  getIntegerOrFloatToken(tokenizer);
}


Token  *getIntegerOrFloatToken(Tokenizer *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  int i = 0;
  while(str[i]!='\0' && str[i]!=' '){
    if(str[i] == '.' || str[i] == 'e')
      return  getFloatToken(tokenizer);
    else
      i++;
  }
  return  getDecimalToken(tokenizer);
}


TokenInteger  *getDecimalToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *resultstr;
  int startColumn = tokenizer->index;
  int i = 0, convertedValue; 
  int size;
  convertedValue = strtol(str, &ptr, 10);
  tokenizer->index += (ptr-str);
  if(*ptr != ' ' && !ispunct(*ptr) && *ptr != '\0'){
    throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid decimal value: %s\n ", str);
  }
  resultstr = duplicateSubstring(str, ptr-str);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);  
}


TokenInteger  *getOctalToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *resultstr, *strnum;
  int startColumn = tokenizer->index;
  int i = 0, convertedValue; 
  int size;
  strnum = str;
  convertedValue = strtol(strnum, &ptr, 8);
  if(*ptr != ' ' && !ispunct(*ptr) && *ptr != '\0')
    throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid octal value: %s\n", str);
  if(*ptr > '7')
    throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid octal value: %s\n", str);
  resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr-str);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);  
}


TokenInteger  *getHexToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *resultstr, *strnum;
  int startColumn = tokenizer->index;
  int i = 0, convertedValue; 
  int size;
  strnum = str + 2; //convert hexadecimal value without 0x
  convertedValue = strtol(strnum, &ptr, 16);
  if(*ptr != ' '&& !ispunct(*ptr) && *ptr != '\0')
    throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid hexadecimal value: %s\n", str);
  resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr-str);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);  
}


TokenFloat  *getFloatToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *resultstr;
  int startColumn = tokenizer->index;
  int i = 0;
  double  convertedValue; 
  int size;
  convertedValue = strtod(str, &ptr);
  if(isalpha(ptr[i])){
    if(ptr[i] == 'e'){
      if(!isdigit(ptr[i+1]) && ptr[i+1] != '+' && ptr[i+1] != '-')
        throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point value: %s\n", str);
      if(!isdigit(ptr[i+2]))
        throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point value: %s\n", str);
      for(int j = i+3; ptr[j] != ' ' && !ispunct(ptr[j]); j++){
        if(isalpha(ptr[j]))
          throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point value(Detected invalid alphabet): %s\n", str);
        if(ptr[j] == '.')
          throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point (multiple dots detected): %s\n", str);
      }
    }
    else{
      throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point value(Detected invalid alphabet): %s\n", str);
    }
  }
  if(*ptr == '.')
    throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point (multiple dots detected): %s\n", str);
  if(*ptr != ' '&& *ptr != '\0' && *ptr != 'e' && !ispunct(*ptr)){
    throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point value: %s\n", str);
  }
  resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr-str);
return  createFloatToken(convertedValue, startColumn, tokenizer->str, resultstr, FLOAT_TYPE);  
}



TokenInteger *getBinToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *strnum;
  int startColumn = tokenizer->index;
  int  convertedValue;
  strnum = str + 2;
  convertedValue = strtol(strnum, &ptr, 2);
  if(*ptr != '1' && *ptr != '0' && *ptr != '\0' && *ptr != ' ' && !ispunct(*ptr))
    throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid binary value: %s\n", str);
  char  *resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr - str);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);
}


TokenIdentifier *getIdentifierToken(Tokenizer *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  int startColumn = tokenizer->index;
  int i = 0;
  while(str[i] != '\0' && str[i] != ' ' && (str[i] == '_' || isalnum(str[i]))){
    i++;
    tokenizer->index++;
  }
  char  *resultstr = duplicateSubstring(str, i);
return  createIdentifierToken(resultstr, startColumn, tokenizer->str, IDENTIFIER_TYPE);  
}



TokenOperator *getOperatorToken(Tokenizer *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  int startColumn = tokenizer->index;
  tokenizer->index++;
  char  *resultstr = duplicateSubstring(str, 1);
  resultstr[1] = '\0';
  tokenizerSkipSpaces(tokenizer);
return  createOperatorToken(resultstr, startColumn, tokenizer->str, OPERATOR_TYPE);  
}


TokenString  *getStringToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  int startColumn = tokenizer->index;
  int i = 0;
  if(str[i] == '\"'){
    i ++;
    tokenizer->index ++;
  }
  else
    throwException(ERROR_INVALID_STRING,NULL, 0, "Invalid string(missing or incomplete symbol \"): %s\n", str);
  while(str[i] != '\"' && str[i] != '\0'){
    i++;
    tokenizer->index++;
  }
  if(str[i] != '\"')
    throwException(ERROR_INVALID_STRING,NULL, 0, "Invalid string(missing or incomplete symbol \"): %s\n", str);
  i ++;
  tokenizer->index ++;
  char  *resultstr = duplicateSubstring(str, i);
  return  createStringToken(resultstr, startColumn, str, STRING_TYPE);
}

