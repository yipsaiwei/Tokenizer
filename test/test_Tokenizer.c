#include "unity.h"
#include "Exception.h"
#include "CException.h"
#include "Tokenizer.h"
#include "Token.h"
#include <malloc.h> 
#include <stdarg.h>

void setUp(void)
{
}

void tearDown(void)
{
}

CEXCEPTION_T ex;


void  test_tokenizerSkipSpaces_given____abc123(){
  Tokenizer *tokenizer = createTokenizer("  abc123"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING(str, "abc123");
  TEST_ASSERT_EQUAL(tokenizer->index, 2);
}

void  test_tokenizerSkipSpaces_given____asterisk(){
  Tokenizer *tokenizer = createTokenizer("     *"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 5);
  TEST_ASSERT_EQUAL_STRING(str, "*");
}

void  test_tokenizerSkipSpaces_given______0x4573_expect_same(){
  Tokenizer *tokenizer = createTokenizer("     0x4573"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 5);
  TEST_ASSERT_EQUAL_STRING(str, "0x4573");
}

void  test_createTokenizer_given_number_expect_same(){
  Tokenizer *tokenizer = createTokenizer("19373");
  TEST_ASSERT_EQUAL_STRING(tokenizer->str, "19373");
  TEST_ASSERT_EQUAL(tokenizer->length, 5);
  freeTokenizer(tokenizer);
}


void  test_getDecimalToken_given_351_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("351"); 
  TokenInteger *token = NULL;
  token = getDecimalToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 3);
  TEST_ASSERT_EQUAL(token->value, 351);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}


void  test_getOctalToken_given_1a35_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1a35"); 
  TokenInteger *token = NULL;
  Try{
  token = getDecimalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}


void  test_getOctalToken_given_035_expect_octal_35(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("035"); 
  TokenInteger *token = NULL;
  token = getOctalToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 3);
  TEST_ASSERT_EQUAL(token->value, 035);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_0o35_expect_octal_35(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0o35"); 
  TokenInteger *token = NULL;
  token = getOctalToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 4);
  TEST_ASSERT_EQUAL(token->value, 035);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_0oa5_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0oa5"); 
  TokenInteger *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_0a5_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0a5"); 
  TokenInteger *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_085_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("085"); 
  TokenInteger *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}


void  test_getHexToken_given_0x55_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0x55"); 
  TokenInteger *token = NULL;
  token = getHexToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 4);
  TEST_ASSERT_EQUAL(token->value, 0x55);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getHexToken_given_0xx5_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0xx5"); 
  TokenInteger *token = NULL;
  Try{
  token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}


void  test_getHexToken_given_00x76_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("00x76"); 
  TokenInteger *token = NULL;
  Try{
  token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}


void  test_getHexToken_given_0xface_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0xface"); 
  TokenInteger *token = NULL;
  token = getHexToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 6);
  TEST_ASSERT_EQUAL(token->value, 0xface);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}


void  test_getHexToken_given_0xAG23_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("00xAG23"); 
  TokenInteger *token = NULL;
  Try{
  token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_1point456_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1.456"); 
  TokenFloat *token = NULL;
  token = getFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 5);
  TEST_ASSERT_EQUAL_FLOAT(token->value, 1.456);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_1apoint456_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1a.456"); 
  TokenFloat *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}


void  test_getFloatToken_given_3pointpoint847_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("3..847"); 
  TokenFloat *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_3point836e2_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("3.836e2"); 
  TokenFloat *token = NULL;
  token = getFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 7);
  TEST_ASSERT_EQUAL_FLOAT(token->value, 3.836e2);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}
  
void  test_getFloatToken_given_53point12eplus2_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("53.12e+2"); 
  TokenFloat *token = NULL;
  token = getFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 8);
  TEST_ASSERT_EQUAL_FLOAT(token->value, 53.12e2);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_18356point123eminus4_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("18356.123e-4"); 
  TokenFloat *token = NULL;
  token = getFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 12);
  TEST_ASSERT_EQUAL_FLOAT(token->value, 18356.123e-4);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_186point13minus4_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("186.13-4"); 
  TokenFloat *token = NULL;
  token = getFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 6);
  TEST_ASSERT_EQUAL_FLOAT(token->value, 186.13);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_1point034eplus3plus12_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1.034e+3+12"); 
  TokenFloat *token = NULL;
  token = getFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 8);
  TEST_ASSERT_EQUAL_FLOAT(token->value, 1.034e+3);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_154xpoint395_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("154x.395"); 
  TokenFloat *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_1point456eplus_plus3_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1.456e++3"); 
  TokenFloat *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}


void  test_getBinToken_given_0b110_expect_decimal_6(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b110"); 
  TokenInteger *token = NULL;
  token = getBinToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 5);
  TEST_ASSERT_EQUAL_FLOAT(token->value, 6);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getBinToken_given_0b1111_expect_decimal_15(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b1111"); 
  TokenInteger *token = NULL;
  token = getBinToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 6);
  TEST_ASSERT_EQUAL_FLOAT(token->value, 15);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given____hihihi123_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("___hihihi123"); 
  TokenIdentifier *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 12);
  TEST_ASSERT_EQUAL_STRING(token->str, "___hihihi123");
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given_totalIsplus123_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("totalIs+123"); 
  TokenIdentifier *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 7);
  TEST_ASSERT_EQUAL_STRING(token->str, "totalIs");
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given_spacex3acerE15_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   acerE15 "); 
  TokenIdentifier *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 10);
  TEST_ASSERT_EQUAL_STRING(token->str, "acerE15");
  TEST_ASSERT_EQUAL(token->startColumn, 3);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getBinToken_given_0b1131_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b1131"); 
  TokenInteger *token = NULL;
  Try{
  token = getBinToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_375_expect_getDecimalToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("375"); 
  TokenInteger *token = NULL;
  token = (TokenInteger *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 3);
  TEST_ASSERT_EQUAL(token->value, 375);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}


void  test_getNumberToken_given_87point9234_expect_getFloatToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("87.9234"); 
  TokenFloat *token = NULL;
  token = (TokenFloat *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 7);
  TEST_ASSERT_EQUAL_FLOAT(token->value, 87.9234);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_0x9521_expect_getHexToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0x9521"); 
  TokenInteger *token = NULL;
  token = (TokenInteger *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 6);
  TEST_ASSERT_EQUAL_HEX(token->value, 0x9521);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_0b1010_expect_getHexToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b1010"); 
  TokenInteger *token = NULL;
  token = (TokenInteger *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 6);
  TEST_ASSERT_EQUAL(token->value, 10);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_0345_expect_getOctToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0345"); 
  TokenInteger *token = NULL;
  token = (TokenInteger *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 4);
  TEST_ASSERT_EQUAL(token->value, 0345);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_32point12point3_expect_getFloatToken_called_exception_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("32.12.3"); 
  TokenFloat *token = NULL;
  Try{
  token = (TokenFloat *)getNumberToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_0b1211_expect_getBinToken_called_exception_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b1211"); 
  TokenInteger *token = NULL;
  Try{
  token = (TokenInteger *)getNumberToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_0x3Y12_expect_getHexToken_called_exception_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0x3Y12"); 
  TokenInteger *token = NULL;
  Try{
  token = (TokenInteger *)getNumberToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_0o318_expect_getOctToken_called_exception_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0o318"); 
  TokenInteger *token = NULL;
  Try{
  token = (TokenInteger *)getNumberToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given_hello_123_expect_without_123(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("hello 123"); 
  TokenIdentifier *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 5);
  TEST_ASSERT_EQUAL_STRING(token->str, "hello");
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}
  
void  test_getIdentifierToken_given_movwf123plus_expect_without_plus(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("movwf123+"); 
  TokenIdentifier *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 8);
  TEST_ASSERT_EQUAL_STRING(token->str, "movwf123");
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}
  
void  test_getOperatorToken_given_plus(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("+"); 
  TokenOperator *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(token->type, OPERATOR_TYPE);
  TEST_ASSERT_EQUAL(tokenizer->index, 1);
  TEST_ASSERT_EQUAL_STRING(token->str, "+");
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
  } 
  
void  test_getToken_given_hello123_expect_getIdentifierToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("hello123"); 
  TokenIdentifier *token = NULL;
  token = (TokenIdentifier  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL(tokenizer->index, 8);
  TEST_ASSERT_EQUAL_STRING(token->str, "hello123");
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getToken_given_6135_expect_getDecimalToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  6135 "); 
  TokenInteger *token = NULL;
  token = (TokenInteger *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 6);
  TEST_ASSERT_EQUAL(token->value, 6135);
  TEST_ASSERT_EQUAL(token->startColumn, 2);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getToken_given_0b10111_expect_getBinToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b10111"); 
  TokenInteger *token = NULL;
  token = (TokenInteger  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(token->type, INTEGER_TYPE);
  TEST_ASSERT_EQUAL(tokenizer->index, 7);
  TEST_ASSERT_EQUAL(token->value, 23);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getToken_given_multiply_expect_getOperatorToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("     *"); 
  TokenOperator *token = NULL;
  token = (TokenOperator  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 6);
  TEST_ASSERT_EQUAL_STRING(token->str, "*");
  TEST_ASSERT_EQUAL(token->startColumn, 5);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getToken_given_spacex3wxyplus_expect_getIdentifierToken_getOperatorToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   wxy+"); 
  TokenIdentifier *token0 = NULL;
  token0 = (TokenIdentifier  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 6);
  TEST_ASSERT_EQUAL_STRING(token0->str, "wxy");
  TEST_ASSERT_EQUAL(token0->startColumn, 3);
  freeToken(token0);
  
  TokenOperator *token1 = NULL;
  token1 = (TokenOperator  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL_STRING(token1->str, "+");
  TEST_ASSERT_EQUAL(tokenizer->index, 7);
  TEST_ASSERT_EQUAL(token1->startColumn, 6);
  freeToken(token1);
  freeTokenizer(tokenizer);
}

void  test_getToken_given_spacex3wxyplus_expect_getHexToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0x349f hello+312-4"); 
  TokenInteger *token0 = NULL;
  token0 = (TokenInteger  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 7);
  TEST_ASSERT_EQUAL_STRING(token0->str, "0x349f");
  TEST_ASSERT_EQUAL(token0->startColumn, 1);
  freeToken(token0);
  
  TokenIdentifier *token1 = NULL;
  token1 = (TokenIdentifier  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL_STRING(token1->str, "hello");
  TEST_ASSERT_EQUAL(tokenizer->index, 13);
  TEST_ASSERT_EQUAL(token1->startColumn, 8);
  freeToken(token1);
  
  TokenOperator *token3 = NULL;
  token3 = (TokenOperator  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL_STRING(token3->str, "+");
  TEST_ASSERT_EQUAL(tokenizer->index, 14);
  TEST_ASSERT_EQUAL(token3->startColumn, 13);
  freeToken(token3);
  
  TokenInteger *token4 = NULL;
  token4 = (TokenInteger *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 17);
  TEST_ASSERT_EQUAL(token4->value, 312);
  TEST_ASSERT_EQUAL(token4->startColumn, 14);
  freeToken(token4);
  freeTokenizer(tokenizer);
}

void  test_getStringToken_Hello_how_are_you_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("\"Hello how are you  \""); 
  TokenString *token = NULL;
  token = getStringToken(tokenizer);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  TEST_ASSERT_EQUAL(tokenizer->index, 21);
  TEST_ASSERT_EQUAL_STRING(token->str, "\"Hello how are you\  \"");
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getStringToken_hi_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("\"hi\""); 
  TokenString *token = NULL;
  token = getStringToken(tokenizer);
  TEST_ASSERT_EQUAL(token->startColumn, 0);
  TEST_ASSERT_EQUAL(tokenizer->index, 4);
  TEST_ASSERT_EQUAL_STRING(token->str, "\"hi\"");
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getStringToken_This_is_a_string_to_test_this_function_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  \"This is a string to test this function.\"   "); 
  TokenString *token = NULL;
  token = getStringToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 43);
  TEST_ASSERT_EQUAL(token->startColumn, 2);
  TEST_ASSERT_EQUAL_STRING(token->str, "\"This is a string to test this function.\"");
  freeToken(token);
  freeTokenizer(tokenizer);
}


void  test_getStringToken_Hello_comma_abcdeQf_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  \"Hello, abcde?f\" "); 
  TokenString *token = NULL;
  token = getStringToken(tokenizer);
  TEST_ASSERT_EQUAL(tokenizer->index, 18);
  TEST_ASSERT_EQUAL_STRING(token->str, "\"Hello, abcde?f\"");
  TEST_ASSERT_EQUAL(token->startColumn, 2);
  freeToken(token);
  freeTokenizer(tokenizer);
}


  

void  test_getStringToken_given_Hello_how_are_you_without_symbol_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("\"Hello how are you  \ "); 
  TokenString *token = NULL;
  Try{
  token = getStringToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_STRING_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
      dumpException(ex);
      TEST_ASSERT_EQUAL(ERROR_INVALID_STRING, ex->errorCode);
      freeException(ex);
    }
  freeTokenizer(tokenizer);
}


/*
void  test_checkTokenType_abc123(){
  Tokenizer *tokenizer = NULL;
  token *Token = NULL;
  tokenizer = createTokenizer("abc123");
  Token = createToken(tokenizer);
   TOKENTYPE type = checkTokenType(Token);
  TEST_ASSERT_EQUAL(type, IDENTIFIER_TYPE);
  freeToken(Token);
  freeTokenizer(tokenizer);
  }

void  test_checkTokenType_0x2345(){
  Tokenizer *tokenizer = NULL;
  token *Token = NULL;
  tokenizer = createTokenizer("0x2345");
  Token = createToken(tokenizer);
   TOKENTYPE type = checkTokenType(Token);
  TEST_ASSERT_EQUAL(type, INTEGER_TYPE);
  freeToken(Token);
  freeTokenizer(tokenizer);
  }
  
void  test_checkTokenType_12point87(){
  Tokenizer *tokenizer = NULL;
  token *Token = NULL;
  tokenizer = createTokenizer("12.87");
  Token = createToken(tokenizer);
  TOKENTYPE type = checkTokenType(Token);
  TEST_ASSERT_EQUAL(type, FLOAT_TYPE);
  freeToken(Token);
  freeTokenizer(tokenizer);
  }
  
void  test_checkTokenType_0b1011(){
  Tokenizer *tokenizer = NULL;
  token *Token = NULL;
  tokenizer = createTokenizer("0b1011");
  Token = createToken(tokenizer);
  TOKENTYPE type = checkTokenType(Token);
  TEST_ASSERT_EQUAL(type, INTEGER_TYPE);
  freeToken(Token);
  freeTokenizer(tokenizer);
  }
  
void  test_checkTokenType_0o354(){
  Tokenizer *tokenizer = NULL;
  token *Token = NULL;
  tokenizer = createTokenizer("0o354");
  Token = createToken(tokenizer);
  TOKENTYPE type = checkTokenType(Token);
  TEST_ASSERT_EQUAL(type, INTEGER_TYPE);
  freeToken(Token);
  freeTokenizer(tokenizer);
  }
  
void  test_checkTokenType_This_is_calendar(){
  Tokenizer *tokenizer = NULL;
  token *Token = NULL;
  tokenizer = createTokenizer("\"This is calendar\"");
  Token = createToken(tokenizer);
  TOKENTYPE type = checkTokenType(Token);
  TEST_ASSERT_EQUAL(type, STRING_TYPE);
  freeToken(Token);
  freeTokenizer(tokenizer);
  }
  
void  test_checkTokenType_plus(){
  Tokenizer *tokenizer = NULL;
  token *Token = NULL;
  tokenizer = createTokenizer("+");
  Token = createToken(tokenizer);
  TOKENTYPE type = checkTokenType(Token);
  TEST_ASSERT_EQUAL(type, OPERATOR_TYPE);
  freeToken(Token);
  freeTokenizer(tokenizer);
  }
  */
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