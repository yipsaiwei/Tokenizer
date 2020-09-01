#include "unity.h"
#include "DoubleLinkedList.h"
#include  "Tokenizer.h"
#include "Exception.h"
#include "CException.h"
#include "Token.h"
//#include  "Data.h"
#include "mock_MemAlloc.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void  test_createTokenizer(){
  char  *str = "Hello World!";
  DoubleLinkedList  list = {NULL, NULL, 0};
  Tokenizer tokenizer = {NULL, 0, 0, NULL};
  memAlloc_ExpectAndReturn(sizeof(Tokenizer), &tokenizer);
  memAlloc_ExpectAndReturn(sizeof(DoubleLinkedList), &list);  
  Tokenizer *tokenizerptr = createTokenizer(str);
  TEST_ASSERT_EQUAL_PTR(&list, tokenizerptr->list);
  TEST_ASSERT_EQUAL_PTR(&tokenizer, tokenizerptr);
}

void  test_freeTokenizer(){
  Tokenizer tokenizer = {NULL, 0, 0, NULL};
  memFree_Expect(&tokenizer);
  freeTokenizer(&tokenizer);
}

void  test_freeTokenizer_with_list(){
  DoubleLinkedList  list = {NULL, NULL, 0};
  Tokenizer tokenizer = {NULL, 0, 0, &list};
  memFree_Expect(&list);
  memFree_Expect(&tokenizer);
  freeTokenizer(&tokenizer);
}

void  test_freeTokenizer_with_list_with_item(){
  Token token = {"123", "123", 0, 3, INTEGER_TYPE};
  ListItem  item = {NULL, NULL, &token};
  DoubleLinkedList  list = {&item, &item, 1};
  Tokenizer tokenizer = {NULL, 0, 0, &list};
  memFree_Expect(token.str);
  memFree_Expect(&token);
  memFree_Expect(&item);
  memFree_Expect(&list);
  memFree_Expect(&tokenizer);
  freeTokenizer(&tokenizer);
}

void  test_createIntToken(){
  TokenInteger  token = {NULL, NULL, 0, 0, INTEGER_TYPE, 0};
  memAlloc_ExpectAndReturn(sizeof(TokenInteger), &token);
  TokenInteger  *tokenptr = createIntToken(23, 9, "         23", "23", INTEGER_TYPE);
  TEST_ASSERT_EQUAL_PTR(&token, tokenptr);
  TEST_ASSERT_EQUAL(23, tokenptr->value);
  TEST_ASSERT_EQUAL(9, tokenptr->startColumn);
  TEST_ASSERT_EQUAL_STRING("         23", tokenptr->originalstr);
  TEST_ASSERT_EQUAL_STRING("23", tokenptr->str);
  TEST_ASSERT_EQUAL(INTEGER_TYPE, tokenptr->type);
}

void  test_createFloatToken(){
  TokenFloat  token = {NULL, NULL, 0, 0, FLOAT_TYPE, 0};
  memAlloc_ExpectAndReturn(sizeof(TokenFloat), &token);
  TokenFloat  *tokenptr = createFloatToken(2.431, 3, "   2.431", "2.431", FLOAT_TYPE);
  TEST_ASSERT_EQUAL_PTR(&token, tokenptr);
  TEST_ASSERT_EQUAL_FLOAT(2.431, tokenptr->value);
  TEST_ASSERT_EQUAL(3, tokenptr->startColumn);
  TEST_ASSERT_EQUAL_STRING("   2.431", tokenptr->originalstr);
  TEST_ASSERT_EQUAL_STRING("2.431", tokenptr->str);
  TEST_ASSERT_EQUAL(FLOAT_TYPE, tokenptr->type);
}

void  test_createIdentifierToken(){
  TokenIdentifier  token = {NULL, NULL, 0, 0, IDENTIFIER_TYPE};
  memAlloc_ExpectAndReturn(sizeof(TokenIdentifier), &token);
  TokenIdentifier  *tokenptr = createIdentifierToken( "Hello123", 2, "  Hello123-  ", IDENTIFIER_TYPE);
  TEST_ASSERT_EQUAL_PTR(&token, tokenptr);
  TEST_ASSERT_EQUAL(2, tokenptr->startColumn);
  TEST_ASSERT_EQUAL_STRING("  Hello123-  ", tokenptr->originalstr);
  TEST_ASSERT_EQUAL_STRING("Hello123", tokenptr->str);
  TEST_ASSERT_EQUAL(IDENTIFIER_TYPE, tokenptr->type);
}

void  test_createStringToken(){
  TokenString  token = {NULL, NULL, 0, 0, STRING_TYPE};
  memAlloc_ExpectAndReturn(sizeof(TokenString), &token);
  TokenString  *tokenptr = createIdentifierToken( "\" A string \"", 1, " \" A string \"  ", STRING_TYPE);
  TEST_ASSERT_EQUAL_PTR(&token, tokenptr);
  TEST_ASSERT_EQUAL(1, tokenptr->startColumn);
  TEST_ASSERT_EQUAL_STRING(" \" A string \"  ", tokenptr->originalstr);
  TEST_ASSERT_EQUAL_STRING("\" A string \"", tokenptr->str);
  TEST_ASSERT_EQUAL(STRING_TYPE, tokenptr->type);
}

void  test_createOperatorToken(){
  TokenOperator  token = {NULL, NULL, 0, 0, OPERATOR_TYPE};
  memAlloc_ExpectAndReturn(sizeof(TokenOperator), &token);
  TokenOperator  *tokenptr = createOperatorToken( "@", 0, "@ ", OPERATOR_TYPE);
  TEST_ASSERT_EQUAL_PTR(&token, tokenptr);
  TEST_ASSERT_EQUAL(0, tokenptr->startColumn);
  TEST_ASSERT_EQUAL_STRING("@ ", tokenptr->originalstr);
  TEST_ASSERT_EQUAL_STRING("@", tokenptr->str);
  TEST_ASSERT_EQUAL(OPERATOR_TYPE, tokenptr->type);
}

void  test_freeToken_without_string(){
  Token token = {NULL, NULL, 0, 0, INTEGER_TYPE};
  memFree_Expect(&token);
  freeToken(&token);
}

void  test_freeToken_with_string(){
  Token token = {"A string", "A string", 0, 0, STRING_TYPE};
  memFree_Expect(token.str);
  memFree_Expect(&token);
  freeToken(&token);
}
