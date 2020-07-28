#ifndef TOKEN_H
#define TOKEN_H



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
}tokenType;

typedef struct
{
	tokenType	type;
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
}token;

typedef struct
{
	tokenType	type;
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
	int		value;
}tokenInt;

typedef struct
{
	tokenType	type;
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
	float		value;
}tokenFloat;

typedef struct
{
	tokenType	type;
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
}tokenIdentifier, tokenString;

typedef struct
{
	tokenType	type;
	char	*originalstr;
	char	*str;
	int		startColumn;
	int		length;
	int		value;
	token	*token[2];
}tokenOperator;
	
tokenInt *createIntToken(int , char *, int , int );
tokenType checkTokenType(char *);

#endif // TOKEN_H