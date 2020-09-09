#include "TokenizerExceptionThrowing.h"
#include "Exception.h"
#include "CException.h"

void  integerExceptionThrowing(char *originalstr, int startColumn, char *message){
  char  *substr = originalstr;
  char  *resultstr;
  int j;
  for(int i = 0; i < startColumn; i++)
    substr++;
  for(j = 0; !isspace(substr[j]) && substr[j] != 0; j++);
  resultstr = duplicateSubstring(substr, j);
  IntegerToken *token = createIntToken(0, startColumn, originalstr, resultstr, TOKEN_INTEGER_TYPE);
  throwException(ERROR_INVALID_INTEGER, token, 0, message);
}

void  floatExceptionThrowing(char *originalstr, int startColumn, char *message){
  char  *substr = originalstr;
  char  *resultstr;
  int j;
  for(int i = 0; i < startColumn; i++)
    substr++;
  for(j = 0; !isspace(substr[j]) && substr[j] != 0; j++);
  resultstr = duplicateSubstring(substr, j);
  FloatToken *token = createFloatToken(0, startColumn, originalstr, resultstr, TOKEN_FLOAT_TYPE);
  throwException(ERROR_INVALID_FLOAT, token, 0, message);
}

void  stringExceptionThrowing(char *originalstr, int startColumn, char *message){
  char  *substr = originalstr;
  char  *resultstr;
  int j;
  for(int i = 0; i < startColumn; i++)
    substr++;
  for(j = 0; substr[j] != 0; j++);
  resultstr = duplicateSubstring(substr, j);
  StringToken *token = createStringToken(resultstr, startColumn, originalstr, TOKEN_STRING_TYPE);
  throwException(ERROR_INVALID_STRING, token, 0, message);
}