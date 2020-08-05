#include "unity.h"
#include "Exception.h"
#include "CException.h"
#include "Tokenizer.h"

void setUp(void)
{
}

void tearDown(void)
{
}

CEXCEPTION_T ex;

void test_skip_white_spaces_Hello(void)
{
  char  *str = skipWhiteSpaces("     Hello");
  TEST_ASSERT_EQUAL(*str, 'H');
}

void test_skip_white_spaces_empty(void)
{
  char  *str = skipWhiteSpaces("         ");
  TEST_ASSERT_EQUAL(*str, 0);
}

void test_Tokenizer_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement Tokenizer");
}

void test_checkIdentifier_given_string_ABCplus3(void)
{
  char  *str = checkIdentifier("ABC+3");
  TEST_ASSERT_EQUAL_STRING(str, "ABC");
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
  TEST_ASSERT_EQUAL(Token->type, IDENTIFIER_TYPE);
  freeToken(Token);
    
  Token = getToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 6);
  TEST_ASSERT_EQUAL_STRING(Token->str, "DEF");
  TEST_ASSERT_EQUAL(Token->type, IDENTIFIER_TYPE);
  freeToken(Token);
    
}

void test_Tokenizer_check_first_token_MOVWF(void)
{

  char  *str = "MOVWF 123";
  Tokenizer *tokenizer = createTokenizer(str);
  tokenizer->token[0] = getToken(tokenizer);
  TEST_ASSERT_EQUAL_STRING(tokenizer->str, "MOVWF 123");
  TEST_ASSERT_EQUAL_STRING(tokenizer->token[0]->str, "MOVWF");
  TEST_ASSERT_EQUAL(tokenizer->index, 5);
  freeTokenizer(tokenizer);
}

void test_Tokenizer_check_first_token_1point2345(void)
{

  char  *str = "1.2345";
  Tokenizer *tokenizer = createTokenizer(str);
  tokenizer->token[0] = getToken(tokenizer);
  TEST_ASSERT_EQUAL_STRING(tokenizer->str, "1.2345");
  TEST_ASSERT_EQUAL_STRING(tokenizer->token[0]->str, "1.2345");
  TEST_ASSERT_EQUAL(tokenizer->index, 6);
  freeTokenizer(tokenizer);
}

void test_Tokenizer_check_first_token_123MOVWF(void)
{
  char  *str = "123MOVWF";
  Tokenizer *tokenizer = createTokenizer(str);
  Try{
  tokenizer->token[0] = getToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
		dumpException(ex);
		TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
		freeException(ex);
	}
  freeTokenizer(tokenizer);
}