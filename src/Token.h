#ifndef TOKEN_H
#define TOKEN_H
#include <stdlib.h>
#include  "MemAlloc.h"
#include "Exception.h"
#include "CException.h"

typedef enum
{
	INTEGER_TYPE,
	FLOAT_TYPE,
	OPERATOR_TYPE,
	IDENTIFIER_TYPE,
	NULL_TYPE,
	STRING_TYPE,
	UNKNOWN_TYPE,
	INVALID_TYPE
}TOKENTYPE;

typedef struct
{
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
  TOKENTYPE	type;
}Token;

typedef struct
{
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
  TOKENTYPE	type;
  int		value;
}IntegerToken;

typedef struct
{
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
  TOKENTYPE	type;
  double		value;
}FloatToken;

typedef struct
{
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
  TOKENTYPE	type;
}IdentifierToken, StringToken;

typedef struct
{
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
  TOKENTYPE	type;
	Token	*token[2];
}OperatorToken;
	
IntegerToken *createIntToken(int  value, int  index, char  *originalstr, char *str, TOKENTYPE  type);
FloatToken *createFloatToken(double  value, int  index, char  *originalstr, char  *str, TOKENTYPE type);
IdentifierToken *createIdentifierToken(char *str, int  index, char  *originalstr, TOKENTYPE type);
StringToken *createStringToken(char *str, int  index, char  *originalstr, TOKENTYPE type);
OperatorToken *createOperatorToken(char *str, int  index, char  *originalstr, TOKENTYPE type);
Token *createNULLToken(char *originalstr, int index, TOKENTYPE type);
void  freeToken(void *token);
void dumpTokenErrorMessage(CEXCEPTION_T ex, int lineNo);

#endif // TOKEN_H