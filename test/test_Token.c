#include "unity.h"
#include "Token.h"
#include  "MemAlloc.h"
#include  "Tokenizer.h"
#include  "DoubleLinkedList.h"
#include "Exception.h"
#include "CException.h"
#include  "TokenizerExceptionThrowing.h"

void setUp(void)
{
}

void tearDown(void)
{
}

CEXCEPTION_T ex;

void  test_createIntToken_given_integer_expect_integer_token_returned(){
  IntegerToken  *token = createIntToken(5335, 2, "  5335 helloWorld", "5335", TOKEN_INTEGER_TYPE);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
  TEST_ASSERT_EQUAL(5335, token->value);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("5335", token->str);
  TEST_ASSERT_EQUAL_STRING("  5335 helloWorld", token->originalstr);
  free(token);
}

void  test_createFloatToken_given_float_expect_float_token_returned(){
  FloatToken  *token = createFloatToken(484.294, 0, "484.294", "484.294Hello", TOKEN_FLOAT_TYPE);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
  TEST_ASSERT_EQUAL_FLOAT(484.294, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("484.294", token->originalstr);
  TEST_ASSERT_EQUAL_STRING("484.294Hello", token->str);
  free(token);
}

void  test_createIdentifierToken_given_identifier_expect_identifier_token_returned(){
  IdentifierToken  *token = createIdentifierToken(" rlcf 0x34", 1, "rlcf", TOKEN_IDENTIFIER_TYPE);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL(1, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("rlcf", token->originalstr);
  TEST_ASSERT_EQUAL_STRING(" rlcf 0x34", token->str);
  free(token);
}

void  test_createStringToken_given_string_expect_string_token_returned(){
  StringToken  *token = createStringToken("  \"Here is the string\" ", 2, "\"Here is the string\"", TOKEN_STRING_TYPE);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token->type);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("\"Here is the string\"", token->originalstr);
  TEST_ASSERT_EQUAL_STRING("  \"Here is the string\" ", token->str);
  free(token);
}

void  test_createOperatorToken_given_operator_expect_operator_token_returned(){
  OperatorToken  *token = createOperatorToken("  + 49382", 2, "+", TOKEN_OPERATOR_TYPE);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("+", token->originalstr);
  TEST_ASSERT_EQUAL_STRING("  + 49382", token->str);
  free(token);
}

void  test_createNULLToken_given_NULL_expect_NULLToken_returned(){
  Token *token = createNULLToken("   ", 3, TOKEN_NULL_TYPE);
  TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE, token->type);
  TEST_ASSERT_EQUAL(3, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("   ", token->originalstr);
  TEST_ASSERT_NULL(token->str);
  TEST_ASSERT_EQUAL(0, token->length);
  free(token);
}

void  test_createNewlineToken_backslash_n_expect_NewLine_token_returned(){
  Token *token = createNewlineToken("\n", 2, "  \n", TOKEN_NEWLINE_TYPE);
  TEST_ASSERT_EQUAL(TOKEN_NEWLINE_TYPE, token->type);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("  \n", token->originalstr);
  TEST_ASSERT_EQUAL_STRING("\n", token->str);
  TEST_ASSERT_EQUAL(1, token->length);
  free(token);
}

//1 +=234
void  test_tokenExpandString_given_a_string_expect_1_char_to_expand(){
  char  *originalstr = memAlloc(sizeof(char) * 8);
  char  *str = memAlloc(sizeof(char) * 3);
  strcpy(originalstr, "1 +=234");
  strcpy(str, "+");
  Token  *token = (Token  *)createOperatorToken(str, 2, originalstr, TOKEN_OPERATOR_TYPE);
  tokenExpandString(token, 1);
  
  TEST_ASSERT_EQUAL_STRING("+=", token->str);
  
  free(token);
}

//1 >>= 232
void  test_tokenExpandString_given_a_string_expect_2_char_to_expand(){
  char  *originalstr = memAlloc(sizeof(char) * 10);
  char  *str = memAlloc(sizeof(char) * 4);
  strcpy(originalstr, "1 >>= 232");
  strcpy(str, ">");
  Token  *token = (Token  *)createOperatorToken(str, 2, originalstr, TOKEN_OPERATOR_TYPE);
  tokenExpandString(token, 2);
  
  TEST_ASSERT_EQUAL_STRING(">>=", token->str);
  
  free(token);
}

void  test_cloneToken_given_a_token_expect_same_information_token_returned(){
  char  *originalstr = memAlloc(sizeof(char) * 10);
  char  *str = memAlloc(sizeof(char) * 4);
  strcpy(originalstr, "1 >>= 232");
  strcpy(str, ">");
  Token  *token = (Token  *)createOperatorToken(str, 2, originalstr, TOKEN_OPERATOR_TYPE);
  Token *newToken = cloneToken(token);
  
  TEST_ASSERT_EQUAL_STRING(">", newToken->str);
  TEST_ASSERT_EQUAL_STRING("1 >>= 232", newToken->originalstr);
  TEST_ASSERT_EQUAL(2, newToken->startColumn);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, newToken->type);
  
  freeToken(newToken);
  free(token);
  free(originalstr);
}

void  test_cloneToken_given_an_intToken_expect_same_information_token_returned(){
  char  *originalstr = memAlloc(sizeof(char) * 10);
  char  *str = memAlloc(sizeof(char) * 4);
  strcpy(originalstr, "  563-777");
  strcpy(str, "563");
  Token  *token = (Token  *)createIntToken(563, 2, originalstr, str, TOKEN_INTEGER_TYPE);
  Token *newToken = cloneToken(token);
  
  TEST_ASSERT_EQUAL(563, ((IntegerToken *)token)->value);
  TEST_ASSERT_EQUAL_STRING("563", newToken->str);
  TEST_ASSERT_EQUAL_STRING("  563-777", newToken->originalstr);
  TEST_ASSERT_EQUAL(2, newToken->startColumn);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, newToken->type);
  
  freeToken(newToken);
  free(token);
  free(originalstr);
}
