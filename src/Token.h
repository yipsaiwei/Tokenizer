#ifndef TOKEN_H
#define TOKEN_H
#include <stdlib.h>
#include  "MemAlloc.h"

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
}TokenInteger;

typedef struct
{
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
  TOKENTYPE	type;
  double		value;
}TokenFloat;

typedef struct
{
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
  TOKENTYPE	type;
}TokenIdentifier, TokenString;

typedef struct
{
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
  TOKENTYPE	type;
	Token	*token[2];
}TokenOperator;
	
TokenInteger *createIntToken(int  value, int  index, char  *originalstr, char *str, TOKENTYPE  type);
TokenFloat *createFloatToken(double  value, int  index, char  *originalstr, char  *str, TOKENTYPE type);
TokenIdentifier *createIdentifierToken(char *str, int  index, char  *originalstr, TOKENTYPE type);
TokenString *createStringToken(char *str, int  index, char  *originalstr, TOKENTYPE type);
TokenOperator *createOperatorToken(char *str, int  index, char  *originalstr, TOKENTYPE type);
Token *createNULLToken(char *originalstr, int index, TOKENTYPE type);
void  freeToken(void *token);

#endif // TOKEN_H