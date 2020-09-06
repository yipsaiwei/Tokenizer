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
  tokenizer->config = 0;
  tokenizer->list = NULL;
  return  tokenizer;
}

void configureTokenizer(Tokenizer *tokenizer, uint32_t configuration){
  tokenizer->config = configuration;
}

void  freeTokenizer(Tokenizer *tokenizer){
  ListItem  *listptr;
  if(tokenizer->list){
    linkedListFreeList(tokenizer->list,  freeToken);
  }
  if(tokenizer != NULL)
    memFree(tokenizer);
}


Token  *getToken(Tokenizer *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
    if(tokenizer->list != NULL){
      if(tokenizer->list->head != NULL)
        return  popToken(tokenizer);  //pop token from doubleLinkedList stored in tokenizer
    }
  if  (isdigit(str[0]))
    return  getNumberToken(tokenizer);
  else  if(isalpha(str[0]) || str[0] == '_')
    return  (Token  *)getIdentifierToken(tokenizer);
  else  if(str[0] == '\"')
    return  (Token  *)getStringToken(tokenizer);
  else  if(str[0] == 0)
    return  createNULLToken(tokenizer->str, tokenizer->index, NULL_TYPE);
  else
    return  (Token  *)getOperatorToken(tokenizer);
}

// Generate the error indicator (^~~~~)
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

// Duplicate a string until given length
char  *duplicateSubstring(char *str, int length){
  char  *resultstr = memAlloc((length+1)*sizeof(char));
  strncpy(resultstr, str, length);
  resultstr[length] = '\0';
  return  resultstr;
}


void  callThrowException(char *message, char *str, int startColumn, int errorType){
  char  *substr = str;
  for(int i = 0; i < startColumn; i++)
    substr++;
  char  *errorLine = errorIndicator(startColumn, substr);
  int x = strlen(errorLine) - startColumn;
  throwException(errorType, errorLine, 1, "%s: %.*s\n%s\n%s\n ", message, x, substr, str, errorLine);
}

// Skip whitespaces of a string
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


//Once the token is pushed back, the token then belongs to tokenizer. 
//Therefore, the token cannot be freed.
void  pushBackToken(Tokenizer *tokenizer, Token *token){
  ListItem  *item = linkedListCreateListItem((void  *)token);
  tokenizer->index = token->startColumn;
  if(tokenizer->list == NULL)
    tokenizer->list = linkedListCreateList();
  linkedListAddItemToHead(item, tokenizer->list);
}

// Remove token from tokenizer->list and return it
Token *popToken(Tokenizer *tokenizer){    
  Token *token;
  ListItem  *item = linkedListRemoveItemFromHead(tokenizer->list);
  token = item->data;
  tokenizer->index = token->length + token->startColumn;
  linkedListFreeListItem(item);
  return  token;
}

// Specify the type of token number here
Token  *getNumberToken(Tokenizer *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr;
  int convertedValue;
  if(str[0] == '0'){
    if(str[1] == 'x')
      return  (Token  *)getHexToken(tokenizer);
    else if(str[1] == 'b')
      return  (Token  *)getBinToken(tokenizer);
    else if(isdigit(str[1]))
      return  (Token  *)getOctalToken(tokenizer);
    else
      return  (Token  *)getDecimalToken(tokenizer);
  }
  else
    return  (Token  *)getDecimalToken(tokenizer);
}


IntegerToken  *getDecimalToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *resultstr;
  int startColumn = tokenizer->index;
  int i = 0, convertedValue; 
  int size;
  convertedValue = strtol(str, &ptr, 10);
  if(*ptr != ' ' && (!ispunct(*ptr) || *ptr == '.') && *ptr != '\0'){
    if(*ptr == '.' || *ptr == 'e')
      return  (IntegerToken *)getFloatToken(tokenizer);
    if ((tokenizer->config &8) && ( *ptr == 'b' || *ptr == 'B'))
     return  getBinToken(tokenizer);
    else  if((tokenizer->config & 2) && ( *ptr == 'h'|| *ptr == 'H' || (*ptr >= 'A' && *ptr <= 'F') || (*ptr >= 'a' && *ptr <= 'f')))
     return  getHexToken(tokenizer);
    else if ((tokenizer->config &4) && (*ptr == 'o' || *ptr == 'O'))
      return  getOctalToken(tokenizer);
   else
    callThrowException("Invalid decimal value", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
  }
  tokenizer->index += (ptr-str);
  resultstr = duplicateSubstring(str, ptr-str);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);  
}


IntegerToken  *getOctalToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *resultstr, *strnum;
  int startColumn = tokenizer->index;
  int i = 0, convertedValue; 
  int size;
  strnum = str;
  convertedValue = strtol(strnum, &ptr, 8);
  if(*ptr != ' ' && (!ispunct(*ptr) || *ptr == '.') && *ptr != '\0'){
    if((tokenizer->config & 4) && (*ptr == 'o' || *ptr == 'O') && (*(ptr+1) == ' ' || *(ptr+1) == 0 || (ispunct(*(ptr+1)) && *(ptr+1) != '_')))
      ptr++;
    else
      callThrowException("Invalid octal value", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
  }
  if(*ptr > '7')
    callThrowException("Invalid octal value(Number >7 detected)", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
  resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr-str);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);  
}


IntegerToken *getBinToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *strnum;
  int startColumn = tokenizer->index;
  int  convertedValue;
  if(str[0] == '0' && str[1] == 'b')
    strnum = str + 2;
  else
      strnum = str;
  convertedValue = strtol(strnum, &ptr, 2);
  if(str[0] == '0' && str[1] == 'b'){
    if(*ptr != '\0' && *ptr != ' ' && !ispunct(*ptr))
      callThrowException("Invalid binary", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
  }
  else{
    if(tokenizer->config & 8){
      if((*ptr == 'B' || *ptr == 'b') && (*(ptr+1) == ' ' || *(ptr+1) == 0 || (ispunct(*(ptr+1)) && *(ptr+1) != '_' && *(ptr+1) != '.')) && str[0] != '0' && str[1] != 'b')
        ptr++;
      else
        callThrowException("Invalid binary", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
    }
    else
      callThrowException("Invalid binary", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
  }
  char  *resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr - str);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);
}


IntegerToken  *getHexToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *resultstr, *strnum;
  int startColumn = tokenizer->index;
  int i = 0, convertedValue; 
  int size;
  if(str[0] == '0' && str[1] == 'x')
    strnum = str + 2; //convert hexadecimal value to without 0x
  else if (str[0] == '$'){
    if(tokenizer->config & 1 && str[1] != '0' && str[2] != 'x')
      strnum = str + 1;
    else
      callThrowException("Invalid hexadecimal value(detected $ and 0x or unconfigured $ sign)", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
  }
  else
    strnum = str;
  convertedValue = strtol(strnum, &ptr, 16);
  if(*ptr != ' '&& (!ispunct(*ptr) || *ptr == '.') && *ptr != '\0'){
    if((str[0] == '0' && str[1] == 'x') || (str[0] == '$'))
      callThrowException("Invalid hexadecimal value", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
    else{
      if(tokenizer->config & 2){
        if((*ptr == 'h' || *ptr == 'H') && ((ispunct(*(ptr+1)) && *(ptr+1) != '_' && *(ptr+1) != '.') || *(ptr+1) == ' ' || *(ptr+1) == 0))
          ptr++;
        else
          callThrowException("Invalid hexadecimal value", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
      }
      else
        callThrowException("Invalid hexadecimal value", tokenizer->str, startColumn, ERROR_INVALID_INTEGER);
    }
  }
  resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr-str);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, INTEGER_TYPE);  
}


FloatToken  *getFloatToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *resultstr;
  int startColumn = tokenizer->index;
  int i = 0;
  double  convertedValue; 
  int size;
  convertedValue = strtod(str, &ptr);
  if(isalpha(ptr[i])){     // when e is detected, check next character
    if(ptr[i] == 'e'){
      if(ptr[i+1] == ' ')
        callThrowException("Invalid floating point value(Expect digits or valid value after 'e')", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
      if(!isdigit(ptr[i+1]) && ptr[i+1] != '+' && ptr[i+1] != '-')
        callThrowException("Invalid floating point value(Invalid operator detected after 'e')", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
      if(!isdigit(ptr[i+2]))
        callThrowException("Invalid floating point value(Invalid digit after operator)", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
      for(int j = i+3; ptr[j] != ' ' && !ispunct(ptr[j]) && ptr[j] != 0; j++){
        if(isalpha(ptr[j]))
          callThrowException("Invalid floating point value(Invalid alphabet detected)", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
        if(ptr[j] == '.')
          callThrowException("Invalid floating point value(Dots detected after 'e')", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
      }
    }
    else
      callThrowException("Invalid floating point value(Invalid alphabet detected)", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
  }
  if(*ptr == '.')
    callThrowException("Invalid floating point value(Multiple dots detected)", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
  if(*ptr != ' '&& *ptr != '\0' && *ptr != 'e' && !ispunct(*ptr) || *ptr == '_')
    callThrowException("Invalid floating point value", tokenizer->str, startColumn, ERROR_INVALID_FLOAT);
  resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr-str);
return  createFloatToken(convertedValue, startColumn, tokenizer->str, resultstr, FLOAT_TYPE);  
}


IdentifierToken *getIdentifierToken(Tokenizer *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  int startColumn = tokenizer->index;
  int i = 0;
  char  *ptr;
  if(tokenizer->config & 2){
    strtol(str, &ptr, 16);
    if((*ptr == 'h' || *ptr == 'H') && !isalnum(*(ptr+1)) && *(ptr+1) != '_')
      return  (IdentifierToken  *)getHexToken(tokenizer);
  }
  while(str[i] != '\0' && str[i] != ' ' && (str[i] == '_' || isalnum(str[i]))){
    i++;
    tokenizer->index++;
  }
  char  *resultstr = duplicateSubstring(str, i);
return  createIdentifierToken(resultstr, startColumn, tokenizer->str, IDENTIFIER_TYPE);  
}


OperatorToken *getOperatorToken(Tokenizer *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  int startColumn = tokenizer->index;
  if((tokenizer->config & 1) && (*str == '$')){
    if(isdigit(*(str+1)) || (*(str+1) >= 'A' && *(str+1) <= 'F') || (*(str+1) >= 'a' && *(str+1) <= 'f'))
      return  (OperatorToken *)getHexToken(tokenizer);
  }
  tokenizer->index++;
  char  *resultstr = duplicateSubstring(str, 1);
  resultstr[1] = '\0';
return  createOperatorToken(resultstr, startColumn, tokenizer->str, OPERATOR_TYPE);  
}


StringToken  *getStringToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  int startColumn = tokenizer->index;
  int i = 0;
  if(str[i] == '\"'){
    i ++;
    tokenizer->index ++;
  }
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

