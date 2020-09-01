#include "Tokenizer.h"
#include "Exception.h"
#include "CException.h"
#include  "string.h"
//#include  "DoubleLinkedList.h"


Tokenizer  *createTokenizer(char *str){
  Tokenizer *tokenizer;
  tokenizer = memAlloc(sizeof(Tokenizer));
  tokenizer->index = 0;
  tokenizer->length = strlen(str);
  tokenizer->str = str;
  tokenizer->list = memAlloc(sizeof(DoubleLinkedList));
  tokenizer->list->head = NULL;
  tokenizer->list->tail = NULL;
  tokenizer->list->count = 0;
  return  tokenizer;
}


void  freeTokenizer(Tokenizer *tokenizer){
  ListItem  *listptr;
  if(tokenizer->list){
    linkedListFreeList(tokenizer->list,  freeToken);
  }
  if(tokenizer != NULL)
    memFree(tokenizer);
}


void  freeToken(void *token){
  Token *tokenFree;
  tokenFree = (Token  *)token;
  if(tokenFree->str)
    memFree(tokenFree->str);
  if(tokenFree)
    memFree(tokenFree);
}

Token  *getToken(Tokenizer *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  if(tokenizer->list->head != NULL)
    return  popToken(tokenizer);
  if  (isdigit(str[0]))
    return  getNumberToken(tokenizer);
  else  if(isalpha(str[0]) || str[0] == '_')
    return  (Token  *)getIdentifierToken(tokenizer);
  else  if(str[0] == '\"')
    return  (Token  *)getStringToken(tokenizer);
  else
    return  (Token  *)getOperatorToken(tokenizer);
}


char  *errorIndicator(int startColumn, char *str){
  int i = startColumn, j = 0, k, l;
  if(str[0] == '\"'){
    for(j = 0; str[j] != 0; j++)
      i++;
    char  *linestr = memAlloc((i+1)*sizeof(char)); //Will be free in throwException
    for(k = 0; k < startColumn; k++)
      linestr[k] = ' ';
    linestr[k] = '^';
    for(l = startColumn+1; l != i; l++)
      linestr[l] = '~';
    linestr[l] = '\0';
    return linestr;     
  }
  for (j = 0; !isspace(str[j]) && str[j] != 0; j++)
    i++;
  char  *linestr = memAlloc((i+1)*sizeof(char));
  for(int k = 0; k != startColumn; k++)
    linestr[k] = ' ';
  linestr[startColumn] = '^';
  for(l = startColumn+1; l != i; l++)
    linestr[l] = '~';
  linestr[l] = '\0';
  return  linestr; 
}


char  *duplicateSubstring(char *str, int length){
  char  *resultstr = memAlloc((length+1)*sizeof(char));
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

void  callThrowException(char *message, char *str, int startColumn, int errorType){
  char  *substr = str;
  for(int i = 0; i < startColumn; i++)
    substr++;
    char  *errorLine = errorIndicator(startColumn, substr);
    int x = strlen(errorLine) - startColumn;
    throwException(errorType,NULL, 0, errorLine, "%s: %.*s\n%s\n%s\n ", message, x, substr, str, errorLine);
}


//Once the token is pushed back, the token then belongs to tokenizer. 
//Therefore, the token cannot be freed.
void  pushBackToken(Tokenizer *tokenizer, Token *token){
  ListItem  *item = linkedListCreateListItem((void  *)token);
  ((Token *)(item->data))->originalstr = tokenizer->str;
  tokenizer->index = token->startColumn;
  linkedListAddItemToHead(item, tokenizer->list);
}

Token *popToken(Tokenizer *tokenizer){
  Token *token;
  ListItem  *item = linkedListRemoveItemFromHead(tokenizer->list);
  token = item->data;
  item->data = NULL;
  tokenizer->index += token->length;
  linkedListFreeListItem(item);
  return  token;
}


Token *duplicateToken(Token  *token){
  Token *newToken;
  newToken = memAlloc(sizeof(Token));
  newToken->originalstr = duplicateSubstring(token->originalstr, strlen(token->originalstr) + 1);
  newToken->str = duplicateSubstring(token->str, strlen(token->str) + 1);
  newToken->startColumn = token->startColumn;
  newToken->length = token->length;
  newToken->type = token->type;
  return  newToken;
}



Token  *getNumberToken(Tokenizer *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  if(str[0] == '0'){
    if(isdigit(str[1]))
      return  (Token  *)getOctalToken(tokenizer);
    else if(str[1] == 'x')
      return  (Token  *)getHexToken(tokenizer);
    else if(str[1] == 'b')
      return  (Token  *)getBinToken(tokenizer);
    else
      return  (Token  *)getOctalToken(tokenizer);
  }
  else
    return  getIntegerOrFloatToken(tokenizer);
}


Token  *getIntegerOrFloatToken(Tokenizer *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  int i = 0;
  while(str[i]!='\0' && str[i]!=' ' && (!ispunct(str[i]) || str[i] == '.')){
    if(str[i] == '.' || str[i] == 'e')
      return  (Token  *)getFloatToken(tokenizer);
    else
      i++;
  }
  return  (Token  *)getDecimalToken(tokenizer);
}


TokenInteger  *getDecimalToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *resultstr;
  int startColumn = tokenizer->index;
  int i = 0, convertedValue; 
  int size;
  convertedValue = strtol(str, &ptr, 10);
  tokenizer->index += (ptr-str);
  if(*ptr != ' ' && !ispunct(*ptr) && *ptr != '\0')
    callThrowException("Invalid decimal value", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
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
    callThrowException("Invalid octal value", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
  if(*ptr > '7')
    callThrowException("Invalid octal value(Number >7 detected)", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
  resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr-str);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);  
}

TokenInteger *getBinToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *strnum;
  int startColumn = tokenizer->index;
  int  convertedValue;
  strnum = str + 2;
  convertedValue = strtol(strnum, &ptr, 2);
  if(*ptr != '1' && *ptr != '0' && *ptr != '\0' && *ptr != ' ' && !ispunct(*ptr))
    callThrowException("Invalid invalid binary", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
  char  *resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr - str);
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
    callThrowException("Invalid hexadecimal value", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
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
  if(isalpha(ptr[i])){     // when e is detected, check next character
    if(ptr[i] == 'e'){
      if(!isdigit(ptr[i+1]) && ptr[i+1] != '+' && ptr[i+1] != '-')
        callThrowException("Invalid floating point value(Invalid operator detected)", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
      if(!isdigit(ptr[i+2]))
        callThrowException("Invalid floating point value", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
      for(int j = i+3; ptr[j] != ' ' && !ispunct(ptr[j]) && ptr[j] != 0; j++){
        if(isalpha(ptr[j]))
          callThrowException("Invalid floating point value(Invalid alphabet detected)", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
        if(ptr[j] == '.')
          callThrowException("Invalid floating point value(Multiple dots detected)", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
      }
    }
    else
      callThrowException("Invalid floating point value(Invalid alphabet detected)", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
  }
  if(*ptr == '.')
    callThrowException("Invalid floating point value(Multiple dots detected)", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
  if(*ptr != ' '&& *ptr != '\0' && *ptr != 'e' && !ispunct(*ptr))
    callThrowException("Invalid floating point value", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
  resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr-str);
return  createFloatToken(convertedValue, startColumn, tokenizer->str, resultstr, FLOAT_TYPE);  
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
  else
    callThrowException("Invalid string(missing or invalid symbol '\"')", tokenizer->str, startColumn, ERROR_INVALID_STRING);
  while(str[i] != '\"' && str[i] != '\0'){
    i++;
    tokenizer->index++;
  }
  if(str[i] != '\"')
    callThrowException("Invalid string(missing or invalid symbol '\"')", tokenizer->str, startColumn, ERROR_INVALID_STRING);
  i ++;
  tokenizer->index ++;
  char  *resultstr = duplicateSubstring(str, i);
  return  createStringToken(resultstr, startColumn, str, STRING_TYPE);
}

