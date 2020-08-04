#include "unity.h"

#include "Tokenizer.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Tokenizer_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement Tokenizer");
}

void test_Tokenizer_test_str(void)
{
    char  *str = "ABC DEF 123";
    Tokenizer *tokenizer = createTokenizer(str);
    TEST_ASSERT_EQUAL_STRING(tokenizer->str, "ABC DEF 123");
}

void test_Tokenizer_check_first_token_ABC(void)
{
    char  *str = "ABC DEF 123";
    Tokenizer *tokenizer = createTokenizer(str);
    TEST_ASSERT_EQUAL_STRING(tokenizer->str, "ABC DEF 123");
    TEST_ASSERT_EQUAL_STRING(tokenizer->token[0]->str, "ABC");
    TEST_ASSERT_EQUAL(tokenizer->index, 3);
    freeTokenizer(tokenizer);
}

void test_Tokenizer_check_first_token_MOVWF(void)
{
    char  *str = "MOVWF 123";
    Tokenizer *tokenizer = createTokenizer(str);
    TEST_ASSERT_EQUAL_STRING(tokenizer->str, "MOVWF 123");
    TEST_ASSERT_EQUAL_STRING(tokenizer->token[0]->str, "MOVWF");
    TEST_ASSERT_EQUAL(tokenizer->index, 5);
    freeTokenizer(tokenizer);
}