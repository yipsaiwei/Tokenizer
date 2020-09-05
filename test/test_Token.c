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

void  test_createIntToken(){
  IntegerToken  *token = createIntToken(5335, 2, "  5335 helloWorld", "5335", INTEGER_TYPE);
  TEST_ASSERT_EQUAL(INTEGER_TYPE, token->type);
  TEST_ASSERT_EQUAL(5335, token->value);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("5335", token->str);
  TEST_ASSERT_EQUAL_STRING("  5335 helloWorld", token->originalstr);
  free(token);
}

void  test_createFloatToken(){
  FloatToken  *token = createFloatToken(484.294, 0, "484.294", "484.294Hello", FLOAT_TYPE);
  TEST_ASSERT_EQUAL(FLOAT_TYPE, token->type);
  TEST_ASSERT_EQUAL_FLOAT(484.294, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("484.294", token->originalstr);
  TEST_ASSERT_EQUAL_STRING("484.294Hello", token->str);
  free(token);
}

void  test_createIdentifierToken(){
  IdentifierToken  *token = createIdentifierToken(" rlcf 0x34", 1, "rlcf", IDENTIFIER_TYPE);
  TEST_ASSERT_EQUAL(IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL(1, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("rlcf", token->originalstr);
  TEST_ASSERT_EQUAL_STRING(" rlcf 0x34", token->str);
  free(token);
}

void  test_createStringToken(){
  StringToken  *token = createStringToken("  \"Here is the string\" ", 2, "\"Here is the string\"", STRING_TYPE);
  TEST_ASSERT_EQUAL(STRING_TYPE, token->type);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("\"Here is the string\"", token->originalstr);
  TEST_ASSERT_EQUAL_STRING("  \"Here is the string\" ", token->str);
  free(token);
}

void  test_createOperatorToken(){
  OperatorToken  *token = createOperatorToken("  + 49382", 2, "+", OPERATOR_TYPE);
  TEST_ASSERT_EQUAL(OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("+", token->originalstr);
  TEST_ASSERT_EQUAL_STRING("  + 49382", token->str);
  free(token);
}