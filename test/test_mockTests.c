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
  Tokenizer tokenizer = {NULL, 0, 0, 0, NULL};
  memAlloc_ExpectAndReturn(sizeof(Tokenizer), &tokenizer); 
  Tokenizer *tokenizerptr = createTokenizer(str);
  TEST_ASSERT_EQUAL_PTR(NULL, tokenizerptr->list);
  TEST_ASSERT_EQUAL_PTR(&tokenizer, tokenizerptr);
}

void  test_freeTokenizer(){
  Tokenizer tokenizer = {NULL, 0, 0, 0, NULL};
  memFree_Expect(&tokenizer);
  freeTokenizer(&tokenizer);
}

void  test_freeTokenizer_with_list(){
  DoubleLinkedList  list = {NULL, NULL, 0};
  Tokenizer tokenizer = {NULL, 0, 0, 0, &list};
  memFree_Expect(&list);
  memFree_Expect(&tokenizer);
  freeTokenizer(&tokenizer);
}

void  test_freeTokenizer_with_list_with_item(){
  Token token = {"123", "123", 0, 3, INTEGER_TYPE};
  ListItem  item = {NULL, NULL, &token};
  DoubleLinkedList  list = {&item, &item, 1};
  Tokenizer tokenizer = {NULL, 0, 0, 0, &list};
  memFree_Expect(token.str);
  memFree_Expect(&token);
  memFree_Expect(&item);
  memFree_Expect(&list);
  memFree_Expect(&tokenizer);
  freeTokenizer(&tokenizer);
}

void  test_createIntToken(){
  IntegerToken  token = {NULL, NULL, 0, 0, INTEGER_TYPE, 0};
  memAlloc_ExpectAndReturn(sizeof(IntegerToken), &token);
  IntegerToken  *tokenptr = createIntToken(23, 9, "         23", "23", INTEGER_TYPE);
  TEST_ASSERT_EQUAL_PTR(&token, tokenptr);
  TEST_ASSERT_EQUAL(23, tokenptr->value);
  TEST_ASSERT_EQUAL(9, tokenptr->startColumn);
  TEST_ASSERT_EQUAL_STRING("         23", tokenptr->originalstr);
  TEST_ASSERT_EQUAL_STRING("23", tokenptr->str);
  TEST_ASSERT_EQUAL(INTEGER_TYPE, tokenptr->type);
}

void  test_createFloatToken(){
  FloatToken  token = {NULL, NULL, 0, 0, FLOAT_TYPE, 0};
  memAlloc_ExpectAndReturn(sizeof(FloatToken), &token);
  FloatToken  *tokenptr = createFloatToken(2.431, 3, "   2.431", "2.431", FLOAT_TYPE);
  TEST_ASSERT_EQUAL_PTR(&token, tokenptr);
  TEST_ASSERT_EQUAL_FLOAT(2.431, tokenptr->value);
  TEST_ASSERT_EQUAL(3, tokenptr->startColumn);
  TEST_ASSERT_EQUAL_STRING("   2.431", tokenptr->originalstr);
  TEST_ASSERT_EQUAL_STRING("2.431", tokenptr->str);
  TEST_ASSERT_EQUAL(FLOAT_TYPE, tokenptr->type);
}

void  test_createIdentifierToken(){
  IdentifierToken  token = {NULL, NULL, 0, 0, IDENTIFIER_TYPE};
  memAlloc_ExpectAndReturn(sizeof(IdentifierToken), &token);
  IdentifierToken  *tokenptr = createIdentifierToken( "Hello123", 2, "  Hello123-  ", IDENTIFIER_TYPE);
  TEST_ASSERT_EQUAL_PTR(&token, tokenptr);
  TEST_ASSERT_EQUAL(2, tokenptr->startColumn);
  TEST_ASSERT_EQUAL_STRING("  Hello123-  ", tokenptr->originalstr);
  TEST_ASSERT_EQUAL_STRING("Hello123", tokenptr->str);
  TEST_ASSERT_EQUAL(IDENTIFIER_TYPE, tokenptr->type);
}

void  test_createStringToken(){
  StringToken  token = {NULL, NULL, 0, 0, STRING_TYPE};
  memAlloc_ExpectAndReturn(sizeof(StringToken), &token);
  StringToken  *tokenptr = createIdentifierToken( "\" A string \"", 1, " \" A string \"  ", STRING_TYPE);
  TEST_ASSERT_EQUAL_PTR(&token, tokenptr);
  TEST_ASSERT_EQUAL(1, tokenptr->startColumn);
  TEST_ASSERT_EQUAL_STRING(" \" A string \"  ", tokenptr->originalstr);
  TEST_ASSERT_EQUAL_STRING("\" A string \"", tokenptr->str);
  TEST_ASSERT_EQUAL(STRING_TYPE, tokenptr->type);
}

void  test_createOperatorToken(){
  OperatorToken  token = {NULL, NULL, 0, 0, OPERATOR_TYPE};
  memAlloc_ExpectAndReturn(sizeof(OperatorToken), &token);
  OperatorToken  *tokenptr = createOperatorToken( "@", 0, "@ ", OPERATOR_TYPE);
  TEST_ASSERT_EQUAL_PTR(&token, tokenptr);
  TEST_ASSERT_EQUAL(0, tokenptr->startColumn);
  TEST_ASSERT_EQUAL_STRING("@ ", tokenptr->originalstr);
  TEST_ASSERT_EQUAL_STRING("@", tokenptr->str);
  TEST_ASSERT_EQUAL(OPERATOR_TYPE, tokenptr->type);
}

void  test_createNULLToken(){
  Token  token = {NULL, NULL, 0, 0, NULL_TYPE};
  memAlloc_ExpectAndReturn(sizeof(Token), &token);
  Token  *tokenptr = createNULLToken( "   ", 3, NULL_TYPE);
  TEST_ASSERT_EQUAL_PTR(&token, tokenptr);
  TEST_ASSERT_EQUAL(3, tokenptr->startColumn);
  TEST_ASSERT_EQUAL_STRING("   ", tokenptr->originalstr);
  TEST_ASSERT_NULL(tokenptr->str);
  TEST_ASSERT_EQUAL(NULL_TYPE, tokenptr->type);
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

void  test_popToken_given_a_token_in_linked_list(){
  Tokenizer tokenizer;
  DoubleLinkedList  list = {NULL, NULL, 0};
  memAlloc_ExpectAndReturn(sizeof(Tokenizer), &tokenizer);
  Tokenizer *tokenizerptr = createTokenizer("  rlcf  0x33 ");
  IdentifierToken token = {"  rlcf  0x33 ", "rlcf", 2, 4, IDENTIFIER_TYPE};
  ListItem  item = {NULL, NULL, &token};
  Token *tokenptr;
  tokenizerptr->list = &list;
  tokenizerptr->list->head = &item;
  tokenizerptr->list->tail = &item;
  tokenizerptr->list->count = 1;
  memFree_Expect(&item);
  tokenptr = popToken(tokenizerptr);
  TEST_ASSERT_EQUAL_PTR(&token, tokenptr);
}

/*
list             item2            item1
head------------>next------------>next-----------   
tail-----        prev<-----------prev           v
count=2 |        &token2         &token1      NULL
        |                         ^
        |_________________________|

*/
void  test_popToken_given_2_tokens_in_linked_list(){
  Tokenizer tokenizer;
  DoubleLinkedList  list = {NULL, NULL, 0};
  memAlloc_ExpectAndReturn(sizeof(Tokenizer), &tokenizer);
  //memAlloc_ExpectAndReturn(sizeof(DoubleLinkedList), &list);
  Tokenizer *tokenizerptr = createTokenizer("  rlcf  0x33 ");
  IdentifierToken token1 = {"  rlcf  0x33 ", "rlcf", 2, 4, IDENTIFIER_TYPE};
  IntegerToken token2 = {"  rlcf  0x33 ", "0x33", 8, 4, INTEGER_TYPE, 0x33};
  ListItem  item1 = {NULL, NULL, &token1};
  ListItem  item2 = {NULL, NULL, &token2};
  Token *tokenptr;
  tokenizerptr->list = &list;
  tokenizerptr->list->head = &item2;
  tokenizerptr->list->tail = &item1;
  tokenizerptr->list->head->next = &item1;
  tokenizerptr->list->head->prev = NULL;
  tokenizerptr->list->tail->next = NULL;
  tokenizerptr->list->tail->prev = &item2;
  tokenizerptr->list->count = 2;
  memFree_Expect(&item2);
  tokenptr = popToken(tokenizerptr);
  TEST_ASSERT_EQUAL_PTR(&token2, tokenptr);
  TEST_ASSERT_EQUAL_PTR(&item1, tokenizerptr->list->head);
  TEST_ASSERT_EQUAL_PTR(&item1, tokenizerptr->list->tail);
  memFree_Expect(&item1);
  tokenptr = popToken(tokenizerptr);
  TEST_ASSERT_EQUAL_PTR(NULL, tokenizerptr->list->head);
  TEST_ASSERT_EQUAL_PTR(NULL, tokenizerptr->list->tail);
}