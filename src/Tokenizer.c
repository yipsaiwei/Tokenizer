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

char  *errorIndicator(int startColumn, char *str){
  int i = startColumn, k ;
  if(str[startColumn] == '\"'){
    int j;
    while(str[i] != '\0')
      i++;
    char  *linestr = malloc((i+1)*sizeof(char));
    for(j = 0; j < startColumn; j++)
      linestr[j] = ' ';
    linestr[j] = '^';
    for(k = startColumn+1; k != i; k++)
      linestr[k] = '~';
    linestr[k] = '\0';
    return linestr;     
  }
  while(!isspace(str[i]) && str[i] != ' ' && str[i] != '\0')
    i++;
  char  *linestr = malloc((i+1)*sizeof(char));
  for(int j = 0; j != startColumn; j++)
    linestr[j] = ' ';
  linestr[startColumn] = '^';
  for(k = startColumn+1; k != i; k++)
    linestr[k] = '~';
  linestr[k] = '\0';
  return  linestr;
  
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
    char  *errorLine = errorIndicator(startColumn, tokenizer->str);
    throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid decimal value: %s\n%s\n%s\n ", str, tokenizer->str, errorLine);
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
  if(*ptr != ' ' && !ispunct(*ptr) && *ptr != '\0'){
    char  *errorLine = errorIndicator(startColumn, tokenizer->str);
    throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid octal value: %s\n%s\n%s\n", str, tokenizer->str, errorLine);
  }
  if(*ptr > '7'){
    char  *errorLine = errorIndicator(startColumn, tokenizer->str);
    throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid octal value: %s\n%s\n%s\n", str, tokenizer->str, errorLine);
  }
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
  if(*ptr != ' '&& !ispunct(*ptr) && *ptr != '\0'){
    char  *errorLine = errorIndicator(startColumn, tokenizer->str);
    throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid hexadecimal value: %s\n%s\n%s\n", str, tokenizer->str, errorLine);
  }
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
      if(!isdigit(ptr[i+1]) && ptr[i+1] != '+' && ptr[i+1] != '-'){
        char  *errorLine = errorIndicator(startColumn, tokenizer->str);
        throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point value: %s\n%s\n%s\n", str, tokenizer->str, errorLine);
      }
      if(!isdigit(ptr[i+2])){
        char  *errorLine = errorIndicator(startColumn, tokenizer->str);
        throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point value: %s\n%s\n%s\n", str, tokenizer->str, errorLine);
      }
      for(int j = i+3; ptr[j] != ' ' && !ispunct(ptr[j]); j++){
        if(isalpha(ptr[j])){
          char  *errorLine = errorIndicator(startColumn, tokenizer->str);
          throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point value(Detected invalid alphabet): %s\n%s\n%s\n", str, tokenizer->str, errorLine);
        }
        if(ptr[j] == '.'){
          char  *errorLine = errorIndicator(startColumn, tokenizer->str);
          throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point (multiple dots detected): %s\n%s\n%s\n", str, tokenizer->str, errorLine);
        }
      }
    }
    else{
      char  *errorLine = errorIndicator(startColumn, tokenizer->str);
      throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point value(Detected invalid alphabet): %s\n%s\n%s\n", str, tokenizer->str, errorLine);
    }
  }
  if(*ptr == '.'){
    char  *errorLine = errorIndicator(startColumn, tokenizer->str);
    throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point (multiple dots detected): %s\n%s\n%s\n", str, tokenizer->str, errorLine);
  }
  if(*ptr != ' '&& *ptr != '\0' && *ptr != 'e' && !ispunct(*ptr)){
    char  *errorLine = errorIndicator(startColumn, tokenizer->str);
    throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point value: %s\n%s\n%s\n", str, tokenizer->str, errorLine);
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
  if(*ptr != '1' && *ptr != '0' && *ptr != '\0' && *ptr != ' ' && !ispunct(*ptr)){
    char  *errorLine = errorIndicator(startColumn, tokenizer->str);
    throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid binary value: %s\n%s\n%s\n", str, tokenizer->str, errorLine);
  }
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
  else{
    char  *errorLine = errorIndicator(startColumn, tokenizer->str);
    throwException(ERROR_INVALID_STRING,NULL, 0, "Invalid string(missing or incomplete symbol \"): %s\n%s\n%s\n", str, tokenizer->str, errorLine);
  }
  while(str[i] != '\"' && str[i] != '\0'){
    i++;
    tokenizer->index++;
  }
  if(str[i] != '\"'){
    char  *errorLine = errorIndicator(startColumn, tokenizer->str);
    throwException(ERROR_INVALID_STRING,NULL, 0, "Invalid string(missing or incomplete symbol \"):%s\n%s\n%s\n", str, tokenizer->str, errorLine);
  }
  i ++;
  tokenizer->index ++;
  char  *resultstr = duplicateSubstring(str, i);
  return  createStringToken(resultstr, startColumn, str, STRING_TYPE);
}

