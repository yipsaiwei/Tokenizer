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
  tokenizer->lineNum = 0;
  return  tokenizer;
}

void configureTokenizer(Tokenizer *tokenizer, uint32_t configuration){
  tokenizer->config = configuration;
}

void  freeTokenizer(Tokenizer *tokenizer){
  DoubleLinkedList  *listptr;
  if(tokenizer->list){
    listptr = tokenizer->list;
    tokenizer->list = NULL;
    linkedListFreeList(listptr,  freeToken);
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
  else  if(str[0] == '\n')
    return  getNewlineToken(tokenizer);
  else  if(str[0] == 0)
    return  createNULLToken(tokenizer->str, tokenizer->index, TOKEN_NULL_TYPE);
  else
    return  (Token  *)getOperatorToken(tokenizer);
}

char  *errorIndicator(int startColumn, int length){
  char  *linestr = memAlloc((startColumn+length+1)*sizeof(char));
  int j;
  for(int i = 0; i < startColumn; i++)
    linestr[i] = ' ';
  linestr[startColumn] = '^';
  for(j = startColumn + 1; j < (length + startColumn); j++)
    linestr[j] = '~';
  linestr[j] = '\0';
  return  linestr;
}

// Duplicate a string until given length
char  *duplicateSubstring(char *str, int length){
  char  *resultstr = memAlloc((length+1)*sizeof(char));
  strncpy(resultstr, str, length);
  resultstr[length] = '\0';
  return  resultstr;
}

// Skip whitespaces of a string
char *tokenizerSkipSpaces(Tokenizer *tokenizer){
  char  *str = tokenizer->str;
  char  *strWithoutSpace;
  for(int i = 0; i<tokenizer->index; i++)
    str++;
  strWithoutSpace = skipWhiteSpaces(str);
  tokenizer->index += (strWithoutSpace - str);
  return  strWithoutSpace;
}

char *skipWhiteSpaces(char  *str){
  while(isspace(*str) && *str != '\n')
    str++;
  return  str;
}

//Once the token is pushed back, the token then belongs to tokenizer. 
//Therefore, the token cannot be freed.
void  pushBackToken(Tokenizer *tokenizer, Token *token){
  ListItem  *item = linkedListCreateListItem((void  *)token);
  if(tokenizer->list == NULL)
    tokenizer->list = linkedListCreateList();
  tokenizer->index = token->startColumn;
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
    if(tolower(str[1]) == 'x')
      return  (Token  *)getHexToken(tokenizer);
    else if(tolower(str[1]) == 'b')
      return  (Token  *)getBinToken(tokenizer);
    else if(isdigit(str[1]))
      return  (Token  *)getOctalToken(tokenizer);
    else
      return  (Token  *)getDecimalOrFloatToken(tokenizer);
  }
  else
    return  (Token  *)getDecimalOrFloatToken(tokenizer);
}

Token  *getDecimalOrFloatToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *resultstr;
  int startColumn = tokenizer->index;
  int i = 0, convertedValue; 
  int size;
  convertedValue = strtol(str, &ptr, 10);
  if(!isspace(*ptr) && (!ispunct(*ptr) || *ptr == '.' || *ptr == '_') && *ptr != '\0'){
    if(*ptr == '.' || *ptr == 'e')
      return  (Token *)getFloatToken(tokenizer);
    if ((tokenizer->config &8) && tolower(*ptr) == 'b' && tolower(*(ptr+1)) != 'h' && tolower(*(ptr+1)) != 'o')
     return  (Token *)getBinToken(tokenizer);
    else  if((tokenizer->config & 2) && ( tolower(*ptr) == 'h'|| (tolower(*ptr) >= 'a' && tolower(*ptr) <= 'f')))
     return  (Token *)getHexToken(tokenizer);
    else if ((tokenizer->config &4) && (tolower(*ptr) == 'o'))
      return  (Token  *)getOctalToken(tokenizer);
   else
     integerExceptionThrowing(tokenizer->str, startColumn, "Invalid decimal value");
  }
  tokenizer->index += (ptr-str);
  resultstr = duplicateSubstring(str, ptr-str);
return  (Token  *)createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, TOKEN_INTEGER_TYPE);  
}

IntegerToken  *getOctalToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *resultstr, *strnum;
  int startColumn = tokenizer->index;
  int i = 0, convertedValue; 
  int size;
  strnum = str;
  convertedValue = strtol(strnum, &ptr, 8);
  if(!isspace(*ptr) && (!ispunct(*ptr) || *ptr == '.' || *ptr == '_') && *ptr != '\0'){
    if((tokenizer->config & 4) && (tolower(*ptr) == 'o') && (isspace(*(ptr+1)) || *(ptr+1) == 0 || (ispunct(*(ptr+1)) && *(ptr+1) != '_' && *(ptr+1) != '.')))
      ptr++;
    else if ((tokenizer->config & 2) && isalnum(*ptr)){
      strtol(strnum, &ptr, 16);
      if(tolower(*ptr) == 'h')
        return  getHexToken(tokenizer);
      else
        integerExceptionThrowing(tokenizer->str, startColumn, "Invalid octal value");
    }
    else  if ((tokenizer->config & 8) && tolower(*ptr) == 'b')
      return  getBinToken(tokenizer);
    else
      integerExceptionThrowing(tokenizer->str, startColumn, "Invalid octal value");
  }
  resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr-str);
  return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, TOKEN_INTEGER_TYPE);  
}

IntegerToken *getBinToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *strnum;
  int startColumn = tokenizer->index;
  int  convertedValue;
  if(str[0] == '0' && tolower(str[1]) == 'b')
    strnum = str + 2;
  else
    strnum = str;
  convertedValue = strtol(strnum, &ptr, 2);
  if(str[0] == '0' && tolower(str[1]) == 'b'){
    if(*ptr != '\0' && !isspace(*ptr) && (!ispunct(*ptr) || *ptr == '.' || *ptr == '_'))
      integerExceptionThrowing(tokenizer->str, startColumn, "Invalid binary value");
  }
  else{
    if(tokenizer->config & 8){
      if((tolower(*ptr) == 'b') && (isspace(*(ptr+1))|| *(ptr+1) == 0 || (ispunct(*(ptr+1)) && *(ptr+1) != '_' && *(ptr+1) != '.')))
        ptr++;
      else
        integerExceptionThrowing(tokenizer->str, startColumn, "Invalid binary value");
    }
    else
      integerExceptionThrowing(tokenizer->str, startColumn, "Invalid binary value");
  }
  char  *resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr - str);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, TOKEN_INTEGER_TYPE);
}

IntegerToken  *getHexToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *resultstr, *strnum;
  int startColumn = tokenizer->index;
  int i = 0, convertedValue; 
  int size;
  if (str[0] == '$'){
    if(tokenizer->config & 1 && (str[1] != '0' || tolower(str[2]) != 'x'))
      strnum = str + 1;
    else
      integerExceptionThrowing(tokenizer->str, startColumn, "Invalid hexadecimal value");
  }
  else
    strnum = str;
  convertedValue = strtol(strnum, &ptr, 16);
  if((!ispunct(*ptr) || *ptr == '.' || *ptr == '_' ) && *ptr != '\0' && !isspace(*ptr)){
    if((str[0] == '0' && tolower(str[1]) == 'x') || (str[0] == '$'))
      integerExceptionThrowing(tokenizer->str, startColumn, "Invalid hexadecimal value");
    else{
      if(tokenizer->config & 2){
        if(tolower(*ptr) == 'h' && ((ispunct(*(ptr+1)) && *(ptr+1) != '_' && *(ptr+1) != '.') || isspace(*(ptr+1)) || *(ptr+1) == 0))
          ptr++;
        else
          integerExceptionThrowing(tokenizer->str, startColumn, "Invalid hexadecimal value");
      }
      else
        integerExceptionThrowing(tokenizer->str, startColumn, "Invalid hexadecimal value");
    }
  }
  resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr-str);
return  createIntToken(convertedValue, startColumn, tokenizer->str, resultstr, TOKEN_INTEGER_TYPE);  
}

FloatToken  *getFloatToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  char  *ptr, *resultstr;
  int startColumn = tokenizer->index;
  int i = 0;
  double  convertedValue; 
  int size;
  convertedValue = strtod(str, &ptr);
  if(!isspace(*ptr) && (!ispunct(*ptr) || *ptr == '_' || *ptr == '.') && *ptr != 0)
    floatExceptionThrowing(tokenizer->str, startColumn,"Invalid floating point value");    
  resultstr = duplicateSubstring(str, ptr-str);
  tokenizer->index += (ptr-str);
return  createFloatToken(convertedValue, startColumn, tokenizer->str, resultstr, TOKEN_FLOAT_TYPE);  
}

IdentifierToken *getIdentifierToken(Tokenizer *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  int startColumn = tokenizer->index;
  int i = 0;
  char  *ptr;
  if(tokenizer->config & 2){
    strtol(str, &ptr, 16);
    if(tolower(*ptr) == 'h' && !isalnum(*(ptr+1)) && *(ptr+1) != '_')
      return  (IdentifierToken  *)getHexToken(tokenizer);
  }
  while(str[i] != '\0' && !isspace(*str) && (str[i] == '_' || isalnum(str[i]))){
    i++;
    tokenizer->index++;
  }
  char  *resultstr = duplicateSubstring(str, i);
return  createIdentifierToken(resultstr, startColumn, tokenizer->str, TOKEN_IDENTIFIER_TYPE);  
}

OperatorToken *getOperatorToken(Tokenizer *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer);
  int startColumn = tokenizer->index;
  if((tokenizer->config & 1) && (*str == '$')){
    if(isdigit(*(str+1)) || (tolower(*(str+1)) >= 'a' && tolower(*(str+1)) <= 'f'))
      return  (OperatorToken *)getHexToken(tokenizer);
  }
  tokenizer->index++;
  char  *resultstr = duplicateSubstring(str, 1);
  resultstr[1] = '\0';
return  createOperatorToken(resultstr, startColumn, tokenizer->str, TOKEN_OPERATOR_TYPE);  
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
    stringExceptionThrowing(tokenizer->str, startColumn, "Invalid string(Missing symbol '\"')");
  i ++;
  tokenizer->index ++;
  char  *resultstr = duplicateSubstring(str, i);
  return  createStringToken(resultstr, startColumn, str, TOKEN_STRING_TYPE);
}

Token *getNewlineToken(Tokenizer  *tokenizer){
  char  *str = tokenizerSkipSpaces(tokenizer); 
  char  *resultstr;
  int startColumn = tokenizer->index;
  tokenizer->lineNum++;
  tokenizer->index++;
  resultstr = duplicateSubstring(str, 1);
  resultstr[1] = 0;
  return  createNewlineToken(resultstr, startColumn, tokenizer->str, TOKEN_NEWLINE_TYPE);
}
