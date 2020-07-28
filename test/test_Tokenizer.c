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

void test_Tokenizer_check_first_token(void)
{
    char  *str = "ABC DEF 123";
    Tokenizer *tokenizer = createTokenizer(str);
    TEST_ASSERT_EQUAL_STRING(tokenizer->str, "ABC DEF 123");
    TEST_ASSERT_EQUAL_STRING(tokenizer->token[0]->str, "ABC");
}