#ifndef TOKEN_H
#define TOKEN_H
#include <stdint.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include  "Errors.h"

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
	TOKENTYPE	type;
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
}token;

typedef struct
{
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
	int		value;
}tokenInt;

typedef struct
{
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
	float		value;
}tokenFloat;

typedef struct
{
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
}tokenIdentifier, tokenString;

typedef struct
{
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
	int		value;
	token	*token[2];
}tokenOperator;
	
//tokenInt *createIntToken(int , char *, int , int );
TOKENTYPE checkTokenType(token  *newToken);

#endif // TOKEN_H