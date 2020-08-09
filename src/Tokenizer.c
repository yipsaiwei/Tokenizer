#include "Tokenizer.h"
#include "Exception.h"
#include "CException.h"

/*
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
  newToken->type = checkTokenType(newToken);
  newToken->length = strlen(newToken->str);
  tokenizer->index += newToken->length;
  return  newToken;
}

token *getNextToken(Tokenizer *tokenizer){
  token *newToken = createToken(tokenizer);
  newToken->type = checkTokenType(newToken);
  newToken->length = strlen(newToken->str);
  tokenizer->index = newToken->length + newToken->startColumn;
  return  newToken;
}
 */ 
  
 /*
token *createToken(Tokenizer  *tokenizer){
  token *newToken = malloc(sizeof(token));
  newToken->originalstr = tokenizer->str;
  newToken->startColumn = tokenizer->index;
  return newToken;
}
*/

/*
tokenInt *createIntToken(Tokenizer  *tokenizer){
  token *newToken = malloc(sizeof(token));
  newToken->originalstr = tokenizer->str;
  newToken->startColumn = tokenizer->index;
  return newToken;
}
*/

/*
void  freeToken(token *Token){
  free(Token);
}

char  *skipWhiteSpaces(char *str, int *i){
  while(isspace(*str)){
    str++;
    *i += 1;
  }
  return  str;
}
*/

/*
TOKENTYPE createToken(Tokenizer  *tokenizer){
  TOKENTYPE type;
  char  *str = moveStrToTokenizerIndex(tokenizer);
  if(isdigit(str[0]))
    type = getNumberToken(str);
  else if (isalpha(str[0]))
    type = getIdentifierToken(str);
  else 
    type = getOperator(str);
}
*/

/*
char  *moveStrToTokenizerIndex(Tokenizer  *tokenizer){
  char  *str = tokenizer->str;
  int i = 0;
  while(i < tokenizer->index){
    str++;
    i++;
  }
  return  str;
}
*/

/*
tokenInt  *getNumberToken(char  *str){
  if(str[0] == '0'){
    if(isdigit(str[1]))
      tokenInt->value = getOctalValue(str);
    else if(str[1] == 'x')
      token->str[1] = getHexValue(str);
    else if(str[1] == 'b')
      token->str = getBinValue(str);
    else
      throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid integer: %s", str);
  }
}
*/
int getDecimalValue(char  *str){
  char  *resultstr = malloc(16*sizeof(char));
  char  *ptr;
  int i = 0, convertedValue;
  while(str[i] != NULL && str[i] != ' '){
    if(!isdigit(str[i]))
      throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid decimal value: %s", str);
    i++;
  }
  strncpy(resultstr, str, i);
  convertedValue = strtol(resultstr, &ptr, 10);
  free(resultstr);
return  convertedValue;  
}


int getOctalValue(char  *str){
  char  *resultstr = malloc(16*sizeof(char));
  char  *ptr;
  int i = 0, convertedValue;
  while(str[i] != NULL && str[i] != ' '){
    if(!isdigit(str[i]))
      throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid octal value: %s", str);
    if(str[i] > '7' || str[i] < '0')
      throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid octal value: %s", str);
    i++;
  }
  strncpy(resultstr, str, i);
  convertedValue = strtol(resultstr, &ptr, 8);
  free(resultstr);
return  convertedValue;  
}


int getHexValue(char  *str){
  char  *resultstr = malloc(16*sizeof(char));
  char  *ptr;
  int i = 2;
  int convertedValue;
  while(str[i] != NULL && str[i] != ' '){
    if(!isdigit(str[i])){
      if(str[i]<'A' || str[i]>'F'){
        if(str[i]<'a' || str[i]>'f')
        throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid hexadecimal value: %s", str);
      }
    }
    i++;
  }
  strncpy(resultstr, str, i);
  convertedValue = strtol(resultstr, &ptr, 16);
  free(resultstr);
return  convertedValue;  
}


double getFloatValue(char  *str){
  char  *resultstr = malloc(16*sizeof(char));
  char  *ptr;
  int i = 0;
  double  convertedValue;
  while(str[i]!='.'){
    if(!(isdigit(str[i])))
      throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point: %s", str);
    i++;
  }
    i++;
  while(str[i]!=NULL && str[i]!= ' '){
    if(!(isdigit(str[i]))){
      if(str[i]== 'e'){
        i++;
        if(str[i]!='+' && str[i]!='-' && (!isdigit(str[i])))
          throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point: %s", str);
      }
      else
        throwException(ERROR_INVALID_FLOAT,NULL, 0, "Invalid floating point: %s", str);
    }
    i++;
  }
  strncpy(resultstr, str, i);
  convertedValue = strtod(resultstr, &ptr);
  free(resultstr);
  return convertedValue;
}

int getBinValue(char  *str){
  char  *resultstr = malloc(16*sizeof(char));
  char  *ptr;
  int i = 0, convertedValue;
  //i++;
  str++;
  while(str[i] != NULL && str[i] != ' '){
    if(str[i]!='0' && str[i]!='1')
      throwException(ERROR_INVALID_INTEGER,NULL, 0, "Invalid binary value: %s", str);
    i++;
  }
  strncpy(resultstr, str, i);
  convertedValue = strtol(resultstr, &ptr, 2);
  free(resultstr);
return  convertedValue;  
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