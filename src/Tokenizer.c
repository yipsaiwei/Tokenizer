#include "Tokenizer.h"

Tokenizer *createTokenizer(char *str){
  Tokenizer *tokenizer;
  tokenizer = malloc(sizeof(Tokenizer));
  tokenizer->index = 0;
  tokenizer->length = strlen(str);
  tokenizer->str = str;
  tokenizer->token[0] = getToken(tokenizer);
  // Will detect type of token here
  return  tokenizer;
}

void  freeTokenizer(Tokenizer *tokenizer){
  free(tokenizer);
}

token *getToken(Tokenizer *tokenizer){
  token *newToken;
  int i = 0;
  char  *str = tokenizer->str;
  char  *tokenstr;
  tokenstr = malloc(sizeof(char));
  while(!(isspace(*str))){
    str++;
    i++;
  }
  tokenizer->index = i;
  for(int j = 0; j<i; j++)
    str--;
  strncpy(tokenstr, str,i);
  newToken = createToken(tokenstr);
  return  newToken;
  
  
}
  
token *createToken(char *tokenstr){
  token *newToken;
  newToken = malloc(sizeof(token));
  newToken->str = tokenstr;
  return newToken;
}