#include "unity.h"
#include "Exception.h"
#include "CException.h"
#include "Tokenizer.h"
#include <malloc.h> 
#include <stdarg.h>

void setUp(void)
{
}

void tearDown(void)
{
}

CEXCEPTION_T ex;

void  test_getDecimalValue_given_035(){
  char  *str = "351";
  int decVal = getDecimalValue(str);
  TEST_ASSERT_EQUAL(decVal, 351);
}

void  test_getDecimalValue_given_1a35(){
  Try{
    char  *str = "1a35";
    int decVal = getDecimalValue(str);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
    }Catch(ex){
      dumpException(ex);
      TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
      freeException(ex);
    }
  }

void  test_getOctalValue_given_035(){
  char  *str = "035";
  int octVal = getOctalValue(str);
  TEST_ASSERT_EQUAL(octVal, 035);
}

void  test_getHexValue_given_0x55(){
  char  *str = "0x55";
  int octVal = getHexValue(str);
  TEST_ASSERT_EQUAL(octVal, 85);
}

void  test_getOctalValue_given_0a5(){
  Try{
    char  *str = "0a5";
    int octVal = getOctalValue(str);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
    }Catch(ex){
      dumpException(ex);
      TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
      freeException(ex);
    }
  }
  
void  test_getOctalValue_given_085(){
  Try{
    char  *str = "085";
    int octVal = getOctalValue(str);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
    }Catch(ex){
      dumpException(ex);
      TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
      freeException(ex);
    }
  }
  
void  test_getHexValue_given_0xx5(){
  Try{
    char  *str = "0xx5";
    int octVal = getHexValue(str);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
    }Catch(ex){
      dumpException(ex);
      TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
      freeException(ex);
    }
}
  
void  test_getHexValue_given_00x76(){
  Try{
    char  *str = "00x76";
    int octVal = getHexValue(str);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
    }Catch(ex){
      dumpException(ex);
      TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
      freeException(ex);
    }
}
  
void  test_getHexValue_given_0xface(){
   char  *str = "0xface";
  int hexVal = getHexValue(str);
  TEST_ASSERT_EQUAL(hexVal, 64206);
  }
  
  
void  test_getHexValue_given_0xG3(){
  Try{
    char  *str = "0xG3";
    int hexVal = getHexValue(str);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
    }Catch(ex){
      dumpException(ex);
      TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
      freeException(ex);
    }
  }
  
void  test_getFloatValue_given_1point456(){
  char  *str = "1.456";
  double floatVal = getFloatValue(str);
  TEST_ASSERT_EQUAL_FLOAT(floatVal, 1.456);
}

void  test_getFloatValue_given_1apoint456(){
  Try{
  char  *str = "1a.456";
  double floatVal = getFloatValue(str);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
      dumpException(ex);
      TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
      freeException(ex);
    }
}

void  test_getFloatValue_given_3pointpoint847(){
  Try{
  char  *str = "3..847";
  double floatVal = getFloatValue(str);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
      dumpException(ex);
      TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
      freeException(ex);
    }
}

void  test_getFloatValue_given_3point836e2(){
  char  *str = "3.836e2";
  double floatVal = getFloatValue(str);
  TEST_ASSERT_EQUAL_FLOAT(floatVal, 383.6);
}


void  test_getFloatValue_given_53point12eplus2(){
  char  *str = "53.12e+2";
  double floatVal = getFloatValue(str);
  TEST_ASSERT_EQUAL_FLOAT(floatVal, 5312);
}
  
  
void  test_getFloatValue_given_18356point123eminus4(){
  char  *str = "18356.123e-4";
  double floatVal = getFloatValue(str);
  TEST_ASSERT_EQUAL_FLOAT(floatVal, 1.8356123);
}


void  test_getFloatValue_given_1point456eplus_plus3(){
  Try{
  char  *str = "1.456e++3";
  double floatVal = getFloatValue(str);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
      dumpException(ex);
      TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
      freeException(ex);
    }
}

void  test_getBinValue_given_b110(){
   char  *str = "b110";
  int binVal = getBinValue(str);
  TEST_ASSERT_EQUAL(binVal, 6);
  }

void  test_getBinValue_given_b1111(){
   char  *str = "b1111";
  int binVal = getBinValue(str);
  TEST_ASSERT_EQUAL(binVal, 15);
  }
  
void  test_getBinValue_given_b1131(){
  Try{
  char  *str = "b1131";
  double binVal = getBinValue(str);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
      dumpException(ex);
      TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
      freeException(ex);
    }
}
/*
void test_skip_white_spaces_Hello(void)
{
  int i = 0;
  char  *str = skipWhiteSpaces("     Hello", &i);
  TEST_ASSERT_EQUAL(*str, 'H');
  TEST_ASSERT_EQUAL(i, 5);
}

void test_skip_white_spaces_empty(void)
{
  int i = 0;
  char  *str = skipWhiteSpaces("         ", &i);
  TEST_ASSERT_EQUAL(*str, 0);
  TEST_ASSERT_EQUAL(i, 9);
}

void test_checkIdentifier_given_string_ABCplus3(void)
{
  char  *str = checkIdentifier("ABC+3");
  int length;
  for (length = 0; str[length]!=NULL; length++);
  TEST_ASSERT_EQUAL(length, 3);
  TEST_ASSERT_EQUAL_STRING(str, "ABC");
}

void test_checkTokenType_given_string_DEF_ABC(void)
{
  char  *str = "   DEF ABC";
  token *Token = NULL;
  Tokenizer *tokenizer = createTokenizer(str);
  Token = createToken(tokenizer);
  Token->originalstr = str;
  Token->type = checkTokenType(Token);
  TEST_ASSERT_EQUAL(Token->type, IDENTIFIER_TYPE);
  TEST_ASSERT_EQUAL_STRING(Token->str, "DEF");
  freeToken(Token);
  freeTokenizer(tokenizer);
}

void test_checkInteger_given_string_123_256(void)
{
  char  *str = "123 256";
  Tokenizer *tokenizer = createTokenizer(str);
  token *Token = createToken(tokenizer);
  Token->str = checkInteger(Token);
  TEST_ASSERT_EQUAL(strlen(Token->str), 3);
  TEST_ASSERT_EQUAL_STRING(Token->str, "123");
}

void test_checkIdentifier_given_string_A37_percentage_54_Space_DEF(void)
{
  char  *str = checkIdentifier("A37%54 DEF");
  TEST_ASSERT_EQUAL_STRING(str, "A37");
}


void test_Tokenizer_test_str(void)
{
  char  *str = "ABC DEF 123";
  Tokenizer *tokenizer = createTokenizer(str);
  TEST_ASSERT_EQUAL_STRING(tokenizer->str, "ABC DEF 123");
}

void test_Tokenizer_check_first_token_ABC(void)
{
  token *Token = NULL;
  char  *str = "ABC DEF 123";
  Tokenizer *tokenizer = createTokenizer(str);
  Token = getToken(tokenizer);
  TEST_ASSERT_EQUAL_STRING(tokenizer->str, "ABC DEF 123");
  TEST_ASSERT_EQUAL_STRING(Token->str, "ABC");
  TEST_ASSERT_EQUAL(tokenizer->index, 3);
  TEST_ASSERT_EQUAL(Token->length, 3);
  TEST_ASSERT_EQUAL(Token->type, IDENTIFIER_TYPE);
  freeToken(Token);
    
  Token = getNextToken(tokenizer);
  TEST_ASSERT_EQUAL(Token->length, 3);
  TEST_ASSERT_EQUAL(Token->startColumn, 4);
  TEST_ASSERT_EQUAL(tokenizer->index, 7);
  TEST_ASSERT_EQUAL_STRING(Token->str, "DEF");
  TEST_ASSERT_EQUAL(Token->type, IDENTIFIER_TYPE);
  freeToken(Token);
  freeTokenizer(tokenizer);
    
}

void test_Tokenizer_check_first_token_MOVWF(void)
{

  char  *str = "MOVWF 123";
  Tokenizer *tokenizer = createTokenizer(str);
  token *Token = NULL;
  Token = getToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 5);
  TEST_ASSERT_EQUAL_STRING(tokenizer->str, "MOVWF 123");
  TEST_ASSERT_EQUAL_STRING(Token->str, "MOVWF");
  TEST_ASSERT_EQUAL(Token->type, IDENTIFIER_TYPE);
  freeToken(Token);
  
  Token = getNextToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 8);
  TEST_ASSERT_EQUAL_STRING(Token->str, "123");
  TEST_ASSERT_EQUAL(Token->type, INTEGER_TYPE);
  
  freeTokenizer(tokenizer);
  freeToken(Token);
}

void test_Tokenizer_check_first_token_1point2345(void)
{

  char  *str = "1.2345";
  Tokenizer *tokenizer = createTokenizer(str);
  token *Token = NULL;
  Token = getToken(tokenizer);
  TEST_ASSERT_EQUAL_STRING(tokenizer->str, "1.2345");
  TEST_ASSERT_EQUAL_STRING(Token->str, "1.2345");
  TEST_ASSERT_EQUAL(tokenizer->index, 6);
  freeTokenizer(tokenizer);
}

void test_Tokenizer_check_first_token_123MOVWF(void)
{
  char  *str = "123MOVWF";
  Tokenizer *tokenizer = createTokenizer(str);
  token *Token = NULL;
  
  Try{
  Token = getToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
		dumpException(ex);
		TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
		freeException(ex);
	}
  freeTokenizer(tokenizer);
}

void test_Tokenizer_check_first_token_35point83point33(void)
{
  char  *str = "35.83.33";
  Tokenizer *tokenizer = createTokenizer(str);
  token *Token = NULL;
  Try{
  Token = getToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
		dumpException(ex);
		TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
		freeException(ex);
	}
  freeTokenizer(tokenizer);
}

void test_Tokenizer_check_first_token_35point83c3(void)
{
  char  *str = "35.83c3";
  Tokenizer *tokenizer = createTokenizer(str);
  token *Token = NULL;
  Try{
  Token = getToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
		dumpException(ex);
		TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
		freeException(ex);
	}
  freeTokenizer(tokenizer);
}

void test_Tokenizer_check_first_token_35point34e8(void)
{
  char  *str = "35.34e8";
  Tokenizer *tokenizer = createTokenizer(str);
  token *Token = NULL;
  Token = getToken(tokenizer);
  TEST_ASSERT_EQUAL_STRING(Token->str, "35.34e8");
  TEST_ASSERT_EQUAL(tokenizer->index, 7);
  freeTokenizer(tokenizer);
}
*/