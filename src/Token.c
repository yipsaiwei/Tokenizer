#include "Token.h"
#include <stdlib.h>
#include <stdio.h> 

tokenInt *createIntToken(char *str){
  tokenInt *newToken = malloc(sizeof(tokenInt));
  newToken->originalstr = str;
  return newToken;
}

// Separate a string based on ' ' or operators into smaller chunk 
// Check the type of token (ASCII?)
// Create and store the token
// 

/*
tokenType checkTokenType(char *str)
{
	printf("%s",*str);
	if (isalpha(str[0]))
	{
    for(int i = 0; i<strlen(str); i++)
    {
      if (
    }
		return IDENTIFIER_TYPE;
	}
  else if ((str[0]>='!'&&str[0]<='/')||(str[0]>=':'&&str[0]<='@')||(str[0]>='['&&str[0]<='`')||(str[0]>='{'&&str[0]<='~'))
		return OPERATOR_TYPE;
  else if (isdigit(str[0]))
	{
		if(str[0]==0&&str[1]=='x')
			return INTEGER_TYPE;	//Hexadecimal
		for (int i=1; str[i]!=NULL; i++)
		{
			if(isalpha(str[i]))
				printf("Invalid...");  //Exception to be implemented
			else if (str[i]='.')
			{
				int isFloat=0;
				if	(isFloat=1)
					printf("There are two '.' found");  //Exception to be implemented
				isFloat=1;
			}
			
		}
		if (isFloat(str))
			return FLOAT_TYPE;
		else
			return INTEGER_TYPE;
	}
	else if (str[0]=='"')
	{
		int i=1;
		int isString=0;
		while (str[i]!=NULL||str[i]!='"')
		{
			if(str[i]=='"')
			{
				isString=1;
				return STRING_TYPE;
			}
			else
			{
        printf("Invalid ...");
				// Exception to be implemented
			}
		}
	}
}
*/

//for operator : if((str[i]>='!'&&str[i]<='/')||(str[i]>=':'&&str[i]<='@')||(str[i]>='['&&str[i]<='`')||(str[i]>='{'&&str[i]<='~'))