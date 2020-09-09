#ifndef TOKENIZEREXCEPTIONTHROWING_H
#define TOKENIZEREXCEPTIONTHROWING_H
#include <ctype.h>
#include  "Tokenizer.h"
#include  "Token.h"

void  integerExceptionThrowing(char *originalstr, int startColumn, char *message);
void  floatExceptionThrowing(char *originalstr, int startColumn, char *message);
void  stringExceptionThrowing(char *originalstr, int startColumn, char *message);

#endif // TOKENIZEREXCEPTIONTHROWING_H
