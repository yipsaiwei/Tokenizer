#include "Tokenizer.h"
#include "Exception.h"
#include "CException.h"


Tokenizer  *createTokenizer(char *str){
  Tokenizer *tokenizer;
  tokenizer = malloc(sizeof(Tokenizer));
  tokenizer->index = 0;
  tokenizer->length = strlen(str);
  tokenizer->str = str;
  return  tokenizer;
}


void  freeTokenizer(Tokenizer *tokenizer){
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

Token  *getNextToken(Tokenizer *tokenizer){
  Token *newToken = createToken(tokenizer);
  //newToken->type = checkTokenType(newToken);
  newToken->length = strlen(newToken->str);
  tokenizer->index = newToken->length + newToken->startColumn;
  return  newToken;
}

 
Token  *createToken(Tokenizer  *tokenizer){
  Token *newToken = malloc(sizeof(Token));
  newToken->originalstr = tokenizer->str;
  newToken->startColumn = tokenizer->index;
  return newToken;
}


void  freeToken(Token *token){
  if(token->str != NULL)
    free(token->str);
  if(token != NULL)
    free(token);
}

/*
char  *skipWhiteSpaces(char *str, int *i){
  while(isspace(*str)){
    str++;
    *i += 1;
  }
  return  str;
}
*/
char  *duplicateString(char *str, int length){
  char  *resultstr = malloc(length*sizeof(char));
  strncpy(resultstr, str, length);
  return  resultstr;
}

char *tokenizerSkipSpaces(Tokenizer *tokenizer){
  char  *str = tokenizer->str;
  while(isspace((tokenizer->str)[tokenizer->index] )){     
    (tokenizer->index) ++;
    str++;
  }
  return  str;
}

char  *returnStringAtTokenizerIndex(Tokenizer *tokenizer){
  char  *str = tokenizer->str;
  int i = 0;
  while (i != tokenizer->index){
    str++;
    i++;
  }
  return  str;
}


Token  *getNumberToken(Tokenizer *tokenizer){
  char  *str = returnStringAtTokenizerIndex(tokenizer);
  if(str[0] == '0'){
    if(str[1] == 'o')
      return  getOctalToken(tokenizer);
    else if(str[1] == 'x')
      return  getHexToken(tokenizer);
    else if(str[1] == 'b')
      return  getBinToken(tokenizer);
    else
      return  getOctalToken(tokenizer);
  }
  else{
    if(isdigit(str[0]))
      return  getIntegerOrFloatToken(tokenizer);
  }
}


Token  *getIntegerOrFloatToken(Tokenizer *tokenizer){
  char  *str = returnStringAtTokenizerIndex(tokenizer);
  int i = 0;
  while(str[i]!=NULL && str[i]!=' '){
    if(str[i] == '.' || str[i] == 'e')
      return  getFloatToken(tokenizer);
    else
      i++;
  }
  return  getDecimalToken(tokenizer);
}


TokenInteger  *getDecimalToken(Tokenizer  *tokenizer){
  char  *str = returnStringAtTokenizerIndex(tokenizer);
  char  *ptr, *resultstr;
  int startColumn = tokenizer->index;
  int i = 0, convertedValue; 
  int size;
  convertedValue = strtol(str, &ptr, 10);
  if(*ptr != ' ' && !ispunct(*ptr) && *ptr != NULL)
    throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid decimal value: %s", str);
  resultstr = duplicateString(str, ptr-str);
  tokenizer->index += (ptr-str);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);  
}


TokenInteger  *getOctalToken(Tokenizer  *tokenizer){
  char  *str = returnStringAtTokenizerIndex(tokenizer);
  char  *ptr, *resultstr;
  int startColumn = tokenizer->index;
  int i = 0, convertedValue; 
  int size;
  if(str[0] == '0' && str[1] == 'o'){
    str++;
    str++;
  }
  convertedValue = strtol(str, &ptr, 8);
  if(*ptr != ' ' && !ispunct(*ptr) && *ptr != NULL)
    throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid octal value: %s", str);
  if(str[0] != '0'){
  str--;
  str--;
  }
  resultstr = duplicateString(str, ptr-str);
  tokenizer->index += (ptr-str);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);  
}


TokenInteger  *getHexToken(Tokenizer  *tokenizer){
  char  *str = returnStringAtTokenizerIndex(tokenizer);
  char  *ptr, *resultstr;
  int startColumn = tokenizer->index;
  int i = 0, convertedValue; 
  int size;
  if(str[0] == '0' && str[1] == 'x'){
    str++;
    str++;
  }
  convertedValue = strtol(str, &ptr, 16);
  if(*ptr != ' '&& !ispunct(*ptr) && *ptr != NULL)
    throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid hexadecimal value: %s", str);
  str--;
  str--;
  resultstr = duplicateString(str, ptr-str);
  tokenizer->index += (ptr-str);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);  
}

TokenFloat  *getFloatToken(Tokenizer  *tokenizer){
  char  *str = returnStringAtTokenizerIndex(tokenizer);
  char  *ptr, *resultstr;
  int startColumn = tokenizer->index;
  int i = 0;
  double  convertedValue; 
  int size;
  convertedValue = strtod(str, &ptr);
  if(isalpha(ptr[i]) && ptr[i] == 'e'){
    if(ispunct(ptr[i+1]) && ispunct(ptr[i+2]))
      throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point value: %s", str);
  }
    
  if(*ptr != ' '&& *ptr != NULL && *ptr != 'e'){
    throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point value: %s", str);
  }
  resultstr = duplicateString(str, ptr-str);
  tokenizer->index += (ptr-str);
return  createFloatToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);  
}

/*
TokenInteger  *getOctalToken(Tokenizer  *tokenizer){
  char  *resultstr = malloc(16*sizeof(char));
  char  *str = returnStringAtTokenizerIndex(tokenizer);
  char  *ptr;
  int i = 0;
  int startColumn = tokenizer->index;
  int convertedValue;
  i++;
  tokenizer->index++;
  if(!isdigit(str[i])){
    if(str[i] == 'o'){
      i++;
      tokenizer->index++;
    }
    else
      throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid octal value: %s", str);
  }
  while(str[i] != NULL && str[i] != ' '){
    if(!isdigit(str[i]))
      throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid octal value: %s", str);
    if(str[i] > '7' || str[i] < '0')
      throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid octal value: %s", str);
    i++;
    tokenizer->index++;
  }
  strncpy(resultstr, str, i);
  resultstr[i] == NULL;
  if(resultstr[1] == 'o'){
    resultstr++;          //skip 0o
    resultstr++;
    convertedValue = strtol(resultstr, &ptr, 8);
    resultstr--;
    resultstr--;
  }
  else
    convertedValue = strtol(resultstr, &ptr, 8);
  tokenizerSkipSpaces(tokenizer);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);  
}
*/


/*
TokenInteger  *getHexToken(Tokenizer *tokenizer){
  char  *resultstr = malloc(16*sizeof(char));
  char  *str = returnStringAtTokenizerIndex(tokenizer);
  char  *ptr;
  int i = 0;
  int startColumn = tokenizer->index;
  int convertedValue;
  if(str[0] == '0' && str[1] == 'x'){
    i=2;
    tokenizer->index=2;    
  }
  else
    throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid hexadecimal value: %s", str);
  while(str[i] != NULL && str[i] != ' '){
    if(!isdigit(str[i])){
      if(str[i]<'A' || str[i]>'F'){
        if(str[i]<'a' || str[i]>'f')
        throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid hexadecimal value: %s", str);
      }
    }
    i++;
    tokenizer->index++;
  }
  strncpy(resultstr, str, i);
  resultstr[i] = NULL;
  convertedValue = strtol(resultstr, &ptr, 16);
  //free(resultstr);
  tokenizerSkipSpaces(tokenizer);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);  
}
*/

/*
TokenFloat *getFloatToken(Tokenizer  *tokenizer){
  char  *resultstr = malloc(16*sizeof(char));
  char  *str = returnStringAtTokenizerIndex(tokenizer);
  char  *ptr;
  int i = 0;
  int startColumn = tokenizer->index;
  double  convertedValue;
  while(str[i]!='.'){
    if(!(isdigit(str[i])))
      throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point: %s", str);
    i++;
    tokenizer->index++;
  }
    i++;
    tokenizer->index++;
  while(str[i]!=NULL && str[i]!= ' '){
    if(!(isdigit(str[i]))){
      if(str[i]== 'e'){
        i++;
        tokenizer->index++;
        if(str[i]!='+' && str[i]!='-' && (!isdigit(str[i])))
          throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point: %s", str);
      }
      else
        throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point: %s", str);
    }
    i++;
    tokenizer->index++;
  }
  strncpy(resultstr, str, i);
  resultstr[i] = NULL;
  convertedValue = strtod(resultstr, &ptr);
  tokenizerSkipSpaces(tokenizer);
  return createFloatToken(convertedValue, startColumn, tokenizer->str, FLOAT_TYPE);
}
*/

TokenInteger *getBinToken(Tokenizer  *tokenizer){
  char  *resultstr = malloc(16*sizeof(char));
  char  *str = returnStringAtTokenizerIndex(tokenizer);
  char  *ptr;
  int startColumn = tokenizer->index;
  int i = 2, convertedValue;
  tokenizer->index += 2;
  while(str[i] != NULL && str[i] != ' '){
    if(str[i]!='0' && str[i]!='1')
      throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid binary value: %s", str);
    i++;
    tokenizer->index++;
  }
  strncpy(resultstr, str, i);
  resultstr[i] = NULL;
  resultstr++;                  //skip 0b
  resultstr++;
  convertedValue = strtol(resultstr, &ptr, 2);
  resultstr--;
  resultstr--;
  tokenizerSkipSpaces(tokenizer);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);
}


TokenIdentifier *getIdentifierToken(Tokenizer *tokenizer){
  char  *resultstr = malloc(16*sizeof(char));
  char  *str = returnStringAtTokenizerIndex(tokenizer);
  int startColumn = tokenizer->index;
  int i = 0;
  while(str[i] != NULL && str[i] != ' ' && str[i] != '_' && isalnum(str[i])){
    i++;
    tokenizer->index++;
  }
  strncpy(resultstr, str, i);
  resultstr[i] = NULL;
  //free(resultstr);
  tokenizerSkipSpaces(tokenizer);
return  createIdentifierToken(resultstr, startColumn, tokenizer->str, IDENTIFIER_TYPE);  
}


TokenOperator *getOperatorToken(Tokenizer *tokenizer){
  int size;
  char  *resultstr = malloc(16*sizeof(char));
  char  *str = returnStringAtTokenizerIndex(tokenizer);
  int startColumn = tokenizer->index;
  tokenizer->index++;
  strncpy(resultstr, str, 1);
  resultstr[1] = NULL;
  //free(resultstr);
  tokenizerSkipSpaces(tokenizer);
return  createOperatorToken(resultstr, startColumn, tokenizer->str, OPERATOR_TYPE);  
}


TokenString  *getStringToken(Tokenizer  *tokenizer){
  char  *resultstr = malloc(32*sizeof(char));
  char  *str = returnStringAtTokenizerIndex(tokenizer);
  int startColumn = tokenizer->index;
  int i = 1;
  tokenizer->index++;
  while(str[i] != '\"' && str[i] != NULL){
    i++;
    tokenizer->index++;
  }
  if(str[i] != '\"')
    throwException(ERROR_INVALID_STRING,NULL, 0, "Invalid string(missing or incomplete symbol \"): %s", str);
  i++;
  tokenizer->index++;
  strncpy(resultstr, str, i);
  resultstr[i] = NULL;
  return  createStringToken(resultstr, startColumn, str, STRING_TYPE);
}

/*
TOKENTYPE checkTokenType(token  *newToken){
  char  *str = newToken->originalstr;
  TOKENTYPE  type;
  for(int a = 0; a < newToken->startColumn; a++)
    str++;
  if(isspace(*str))
    str = skipWhiteSpaces(str, &newToken->startColumn);
  if(isalpha(*str)){
    newToken->str = checkIdentifier(str);
    newToken->length = strlen(newToken->str);
    return  IDENTIFIER_TYPE;
  }
  else  //if(isdigit(*str)){
    {
    newToken->str = checkInteger(newToken);
  }
}


char *checkIdentifier(char  *str){
  int i = 0;
  char  *tokenstr = malloc(sizeof(char));
  while(isalnum(str[i])){
    i++;
  }
  strncpy(tokenstr, str,(i));
  tokenstr[i] = '\0';
  return  tokenstr;
}


char  *checkInteger(token *Token){
  int i = 0;
  char  *str = Token->originalstr;
  char  *resultstr = malloc(sizeof(char));
  while(str[i]!=NULL && str[i]!=' '){
    if(isalpha(str[i]))
      throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid integer: %s", str);
    if(str[i]=='.'){
      resultstr = checkFloat(str);
      Token->type = FLOAT_TYPE;
      return  resultstr;
    }
    i++;
  }
  Token->type = INTEGER_TYPE;
  strncpy(resultstr, str, i);
  resultstr[i] = '\0';
  return  resultstr;
}



char  *checkFloat(char  *str){
  int j = 0;
  char  *resultstr = malloc(sizeof(char));
  while(str[j] != '.'){   //Move the pointer to after the '.'
    j++;
  }
  j++;
  while(str[j]!=NULL &&str[j]!=' '){  
    if(str[j]=='.')
      throwException(ERROR_INVALID_FLOAT,NULL, 0, "Multiple decimal points detected: %s", str);
    if(!isdigit(str[j])){
      if(str[j]!='e'){
        throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid float: %s", str);
      }
    }
    if(str[j] == 'e'){
      if(str[j+1] == '+' ||str[j+1] == '-'){
        if(str[j+2] == '+' || str[j+2] == '-')
          throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid float (exponential): %s", str);
      }
    }
    j++;
  }
 strncpy(resultstr, str, j);
 resultstr[j] = '\0';
 return resultstr;
  
}
*/