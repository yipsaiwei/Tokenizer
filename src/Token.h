#ifndef TOKEN_H
#define TOKEN_H
#include <stdlib.h>
#include  "MemAlloc.h"
#include "Exception.h"
#include "CException.h"

typedef enum
{
	TOKEN_INTEGER_TYPE,
	TOKEN_FLOAT_TYPE,
	TOKEN_OPERATOR_TYPE,
	TOKEN_IDENTIFIER_TYPE,
	TOKEN_NULL_TYPE,
	TOKEN_STRING_TYPE,
  TOKEN_NEWLINE_TYPE,
	TOKEN_UNKNOWN_TYPE,
	TOKEN_INVALID_TYPE
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
	//Token	*token[2];
}OperatorToken;
	
IntegerToken *createIntToken(int  value, int  index, char  *originalstr, char *str, TOKENTYPE  type);
FloatToken *createFloatToken(double  value, int  index, char  *originalstr, char  *str, TOKENTYPE type);
IdentifierToken *createIdentifierToken(char *str, int  index, char  *originalstr, TOKENTYPE type);
StringToken *createStringToken(char *str, int  index, char  *originalstr, TOKENTYPE type);
OperatorToken *createOperatorToken(char *str, int  index, char  *originalstr, TOKENTYPE type);
Token *createNULLToken(char *originalstr, int index, TOKENTYPE type);
Token *createNewlineToken(char  *str, int index, char  *originalstr, TOKENTYPE type);
void  freeToken(void *token);
void dumpTokenErrorMessage(CEXCEPTION_T ex, int lineNo);
void tokenExpandString(Token  *token, int lengthToExpand);
Token *cloneToken(Token *token);

#endif // TOKEN_H