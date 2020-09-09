#include "unity.h"
#include "Token.h"
#include  "MemAlloc.h"
#include  "Tokenizer.h"
#include  "DoubleLinkedList.h"
#include "Exception.h"
#include "CException.h"

void setUp(void)
{
}

void tearDown(void)
{
}

CEXCEPTION_T ex;

void  test_createIntToken(){
  IntegerToken  *token = createIntToken(5335, 2, "  5335 helloWorld", "5335", TOKEN_INTEGER_TYPE);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
  TEST_ASSERT_EQUAL(5335, token->value);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("5335", token->str);
  TEST_ASSERT_EQUAL_STRING("  5335 helloWorld", token->originalstr);
  free(token);
}

void  test_createFloatToken(){
  FloatToken  *token = createFloatToken(484.294, 0, "484.294", "484.294Hello", TOKEN_FLOAT_TYPE);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
  TEST_ASSERT_EQUAL_FLOAT(484.294, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("484.294", token->originalstr);
  TEST_ASSERT_EQUAL_STRING("484.294Hello", token->str);
  free(token);
}

void  test_createIdentifierToken(){
  IdentifierToken  *token = createIdentifierToken(" rlcf 0x34", 1, "rlcf", TOKEN_IDENTIFIER_TYPE);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL(1, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("rlcf", token->originalstr);
  TEST_ASSERT_EQUAL_STRING(" rlcf 0x34", token->str);
  free(token);
}

void  test_createStringToken(){
  StringToken  *token = createStringToken("  \"Here is the string\" ", 2, "\"Here is the string\"", TOKEN_STRING_TYPE);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token->type);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("\"Here is the string\"", token->originalstr);
  TEST_ASSERT_EQUAL_STRING("  \"Here is the string\" ", token->str);
  free(token);
}

void  test_createOperatorToken(){
  OperatorToken  *token = createOperatorToken("  + 49382", 2, "+", TOKEN_OPERATOR_TYPE);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("+", token->originalstr);
  TEST_ASSERT_EQUAL_STRING("  + 49382", token->str);
  free(token);
}

void  test_createNULLToken(){
  Token *token = createNULLToken("   ", 3, TOKEN_NULL_TYPE);
  TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE, token->type);
  TEST_ASSERT_EQUAL(3, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("   ", token->originalstr);
  TEST_ASSERT_NULL(token->str);
  TEST_ASSERT_EQUAL(0, token->length);
  free(token);
}

void  test_createNewlineToken(){
  Token *token = createNewlineToken("\n", 2, "  \n", TOKEN_NEWLINE_TYPE);
  TEST_ASSERT_EQUAL(TOKEN_NEWLINE_TYPE, token->type);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("  \n", token->originalstr);
  TEST_ASSERT_EQUAL_STRING("\n", token->str);
  TEST_ASSERT_EQUAL(1, token->length);
  free(token);
}

