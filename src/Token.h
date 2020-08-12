#ifndef TOKEN_H
#define TOKEN_H
//#include  "Tokenizer.h"
#include <stdlib.h>

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
	int		value;
  TOKENTYPE	type;
}TokenInteger;

typedef struct
{
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
	double		value;
  TOKENTYPE	type;
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
	int		value;
  TOKENTYPE	type;
	Token	*token[2];
}TokenOperator;
	
TokenInteger *createIntToken(int  value, int  index, char  *originalstr, char *str, TOKENTYPE  type);
TokenFloat *createFloatToken(double  value, int  index, char  *originalstr, char  *str, TOKENTYPE type);
TokenIdentifier *createIdentifierToken(char *str, int  index, char  *originalstr, TOKENTYPE type);
TokenString *createStringToken(char *str, int  index, char  *originalstr, TOKENTYPE type);
TokenOperator *createOperatorToken(char *str, int  index, char  *originalstr, TOKENTYPE type);

#endif // TOKEN_H