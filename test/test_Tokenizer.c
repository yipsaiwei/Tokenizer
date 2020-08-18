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

void  test_createTokenizer_given_number_expect_same(){
  Tokenizer *tokenizer = createTokenizer("19373");
  TEST_ASSERT_EQUAL_STRING("19373", tokenizer->str);
  TEST_ASSERT_EQUAL(5, tokenizer->length);
  freeTokenizer(tokenizer);
}

void  test_createTokenizer_expect_same(){
  Tokenizer *tokenizer = createTokenizer(" Hihihi1038w");
  TEST_ASSERT_EQUAL_STRING(" Hihihi1038w", tokenizer->str);
  TEST_ASSERT_EQUAL(12, tokenizer->length);
  freeTokenizer(tokenizer);
}

void  test_createTokenizer_2_expect_same(){
  Tokenizer *tokenizer = createTokenizer("39472 +1972 ajbdd qq");
  TEST_ASSERT_EQUAL_STRING("39472 +1972 ajbdd qq", tokenizer->str);
  TEST_ASSERT_EQUAL(20, tokenizer->length);
  freeTokenizer(tokenizer);
}

void  test_tokenizerSkipSpaces_given_efnkfsl646(){
  Tokenizer *tokenizer = createTokenizer("efnkfsl646"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING("efnkfsl646", str);
  TEST_ASSERT_EQUAL(0, tokenizer->index);
}

void  test_tokenizerSkipSpaces_given____abc123(){
  Tokenizer *tokenizer = createTokenizer("  abc123"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING("abc123", str);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
}

//Further check this function
void  test_tokenizerSkipSpaces_given_backslash_t(){
  Tokenizer *tokenizer = createTokenizer("\thellllllo"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING("hellllllo", str);
  TEST_ASSERT_EQUAL(1, tokenizer->index);
}


void  test_tokenizerSkipSpaces_given____asterisk(){
  Tokenizer *tokenizer = createTokenizer("     *"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("*", str);
}

void  test_tokenizerSkipSpaces_given______0x4573_expect_same(){
  Tokenizer *tokenizer = createTokenizer("     0x4573"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("0x4573", str);
}

void  test_duplicateSubString_given_a_string_and_length(){
  char  *str = "DuplicateThisString Hi 193452";
  char  *resultstr;
  resultstr = duplicateSubstring(str, 19);
  TEST_ASSERT_EQUAL_STRING("DuplicateThisString", resultstr);
}

void  test_duplicateSubString_2_given_a_string_and_length(){
  char  *str = "This is a test function to test string";
  char  *resultstr;
  resultstr = duplicateSubstring(str, 14);
  TEST_ASSERT_EQUAL_STRING("This is a test", resultstr);
}

void  test_getDecimalToken_given_351_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("351"); 
  TokenInteger *token = NULL;
  token = getDecimalToken(tokenizer);
  TEST_ASSERT_EQUAL(3, tokenizer->index);
  TEST_ASSERT_EQUAL(3, token->length);
  TEST_ASSERT_EQUAL(351, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
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
  TEST_ASSERT_EQUAL(3, tokenizer->index);
  TEST_ASSERT_EQUAL(035, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_01239_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("01239"); 
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

void  test_getOctalToken_given_0o35_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0o35"); 
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
  TEST_ASSERT_EQUAL(4, tokenizer->index);
  TEST_ASSERT_EQUAL(0x55, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
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
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL(0xface, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
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
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(1.456, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
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
  TEST_ASSERT_EQUAL(7, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(3.836e2,token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}
  
void  test_getFloatToken_given_53point12eplus2_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("53.12e+2"); 
  TokenFloat *token = NULL;
  token = getFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(8, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(53.12e2, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_18356point123eminus4_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("18356.123e-4"); 
  TokenFloat *token = NULL;
  token = getFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(12, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(18356.123e-4, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_186point13minus4_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("186.13-4"); 
  TokenFloat *token = NULL;
  token = getFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(186.13, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_1point034eplus3plus12_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1.034e+3+12"); 
  TokenFloat *token = NULL;
  token = getFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(8, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(1.034e+3, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
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

void  test_getFloatToken_given_1point456eminus_minus3_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1.456e--3"); 
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

void  test_getFloatToken_given_1point456emultiply8_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1.456e*8"); 
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
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(6, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getBinToken_given_0b1111_expect_decimal_15(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b1111"); 
  TokenInteger *token = NULL;
  token = getBinToken(tokenizer);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(15, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given____hihihi123_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("___hihihi123"); 
  TokenIdentifier *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(12, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("___hihihi123", token->str);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given_totalIsplus123_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("totalIs+123"); 
  TokenIdentifier *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(7, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("totalIs", token->str);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given_spacex3acerE15_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   acerE15 "); 
  TokenIdentifier *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(10, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("acerE15", token->str);
  TEST_ASSERT_EQUAL(3, token->startColumn);
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
  TEST_ASSERT_EQUAL(3, tokenizer->index);
  TEST_ASSERT_EQUAL(375, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}


void  test_getNumberToken_given_87point9234_expect_getFloatToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("87.9234"); 
  TokenFloat *token = NULL;
  token = (TokenFloat *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(7, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(87.9234, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_0x9521_expect_getHexToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0x9521"); 
  TokenInteger *token = NULL;
  token = (TokenInteger *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL_HEX(0x9521, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_0b1010_expect_getHexToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b1010"); 
  TokenInteger *token = NULL;
  token = (TokenInteger *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL(10, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_0345_expect_getOctToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0345"); 
  TokenInteger *token = NULL;
  token = (TokenInteger *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(4, tokenizer->index);
  TEST_ASSERT_EQUAL(0345, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
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

void  test_getIntegerOrFloatToken_given_138point1874_expect_getFloatToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   138.1874"); 
  TokenFloat *token = NULL;
  token = (TokenFloat *)getIntegerOrFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(FLOAT_TYPE, token->type);
  TEST_ASSERT_EQUAL_FLOAT(138.1874, token->value);
  TEST_ASSERT_EQUAL(11, tokenizer->index);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIntegerOrFloatToken_given_87e2_expect_getFloatToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  87e2"); 
  TokenFloat *token = NULL;
  token = (TokenFloat *)getIntegerOrFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(FLOAT_TYPE, token->type);
  TEST_ASSERT_EQUAL_FLOAT(87e2, token->value);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIntegerOrFloatToken_given_4532_expect_getIntegerToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 4532"); 
  TokenInteger *token = NULL;
  token = (TokenInteger *)getIntegerOrFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(INTEGER_TYPE, token->type);
  TEST_ASSERT_EQUAL(4532, token->value);
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  freeToken(token);
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
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("hello", token->str);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}
  
void  test_getIdentifierToken_given_movwf123plus_expect_without_plus(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("movwf123+"); 
  TokenIdentifier *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(8, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("movwf123", token->str);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}
  
void  test_getOperatorToken_given_plus(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("+"); 
  TokenOperator *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(1, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("+", token->str);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_minus(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  - "); 
  TokenOperator *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(3, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("-", token->str);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

  
void  test_getToken_given_hello123_expect_getIdentifierToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("hello123"); 
  TokenIdentifier *token = NULL;
  token = (TokenIdentifier  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL(8, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("hello123", token->str);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getToken_given_197e2_expect_getFloatToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  197e2  "); 
  TokenFloat *token = NULL;
  token = (TokenFloat  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(FLOAT_TYPE, token->type);
  TEST_ASSERT_EQUAL(7, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(197e2, token->value);
  TEST_ASSERT_EQUAL_STRING("197e2", token->str);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getToken_given_6135_expect_getDecimalToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  6135 "); 
  TokenInteger *token = NULL;
  token = (TokenInteger *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL(6135, token->value);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getToken_given_12x483_expect_getDecimalToken_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  12x483 "); 
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

void  test_getToken_given_143eminusx2_expect_getFloatToken_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  143e-x2 "); 
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

void  test_getToken_given_384point99eplus3u_expect_getFloatToken_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  384.99e+3u "); 
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

void  test_getToken_given_0b10111_expect_getBinToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b10111"); 
  TokenInteger *token = NULL;
  token = (TokenInteger  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(INTEGER_TYPE, token->type);
  TEST_ASSERT_EQUAL(7, tokenizer->index);
  TEST_ASSERT_EQUAL(23, token->value);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getToken_given_multiply_expect_getOperatorToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("     *"); 
  TokenOperator *token = NULL;
  token = (TokenOperator  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("*", token->str);
  TEST_ASSERT_EQUAL(5, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getToken_given__vifhj_expect_getIdentifierToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    _vifhj+34"); 
  TokenIdentifier *token = NULL;
  token = (TokenIdentifier  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(10, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("_vifhj", token->str);
  TEST_ASSERT_EQUAL(4, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}


void  test_getToken_given_spacex3wxyplus_expect_getIdentifierToken_getOperatorToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   wxy+"); 
  TokenIdentifier *token0 = NULL;
  token0 = (TokenIdentifier  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("wxy", token0->str);
  TEST_ASSERT_EQUAL(3, token0->startColumn);
  freeToken(token0);
  
  TokenOperator *token1 = NULL;
  token1 = (TokenOperator  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL_STRING("+", token1->str);
  TEST_ASSERT_EQUAL(7, tokenizer->index);
  TEST_ASSERT_EQUAL(6, token1->startColumn);
  freeToken(token1);
  freeTokenizer(tokenizer);
}

void  test_getToken_given_spacex3wxyplus_expect_getHexToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0x349f hello+312-4"); 
  TokenInteger *token0 = NULL;
  token0 = (TokenInteger  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(7, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("0x349f", token0->str);
  TEST_ASSERT_EQUAL(1, token0->startColumn);
  freeToken(token0);
  
  TokenIdentifier *token1 = NULL;
  token1 = (TokenIdentifier  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL_STRING("hello", token1->str);
  TEST_ASSERT_EQUAL(13, tokenizer->index);
  TEST_ASSERT_EQUAL(8, token1->startColumn);
  freeToken(token1);
  
  TokenOperator *token3 = NULL;
  token3 = (TokenOperator  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL_STRING("+", token3->str);
  TEST_ASSERT_EQUAL(14, tokenizer->index);
  TEST_ASSERT_EQUAL(13, token3->startColumn);
  freeToken(token3);
  
  TokenInteger *token4 = NULL;
  token4 = (TokenInteger *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(17, tokenizer->index);
  TEST_ASSERT_EQUAL(312, token4->value);
  TEST_ASSERT_EQUAL(14, token4->startColumn);
  freeToken(token4);
  freeTokenizer(tokenizer);
}

void  test_getStringToken_Hello_how_are_you_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("\"Hello how are you  \""); 
  TokenString *token = NULL;
  token = (TokenString  *)getStringToken(tokenizer);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  TEST_ASSERT_EQUAL(21, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("\"Hello how are you\  \"", token->str);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getStringToken_hi_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("\"hi\""); 
  TokenString *token = NULL;
  token = (TokenString  *)getStringToken(tokenizer);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  TEST_ASSERT_EQUAL(4, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("\"hi\"", token->str);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getStringToken_This_is_a_string_to_test_this_function_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  \"This is a string to test this function.\"   "); 
  TokenString *token = NULL;
  token = (TokenString  *)getStringToken(tokenizer);
  TEST_ASSERT_EQUAL(43, tokenizer->index);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("\"This is a string to test this function.\"", token->str);
  freeToken(token);
  freeTokenizer(tokenizer);
}


void  test_getStringToken_Hello_comma_abcdeQf_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  \"Hello, abcde?f\" "); 
  TokenString *token = NULL;
  token = (TokenString  *)getStringToken(tokenizer);
  TEST_ASSERT_EQUAL(18, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("\"Hello, abcde?f\"", token->str);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}


  

void  test_getStringToken_given_Hello_how_are_you_without_symbol_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("\"Hello how are you  \ "); 
  TokenString *token = NULL;
  Try{
  token = (TokenString  *)getStringToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_STRING_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
      dumpException(ex);
      TEST_ASSERT_EQUAL(ERROR_INVALID_STRING, ex->errorCode);
      freeException(ex);
    }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_Peace_123plus67_expect_getHexToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  Peace  123+67\"school\""); 
  TokenIdentifier *token0 = NULL;
  token0 = (TokenIdentifier  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(7, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("Peace", token0->str);
  TEST_ASSERT_EQUAL(2, token0->startColumn);
  freeToken(token0);
  
  TokenInteger *token1 = NULL;
  token1 = (TokenInteger  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL_STRING("123", token1->str);
  TEST_ASSERT_EQUAL(12, tokenizer->index);
  TEST_ASSERT_EQUAL(123, token1->value);
  TEST_ASSERT_EQUAL(9, token1->startColumn);
  freeToken(token1);
  
  TokenOperator *token2 = NULL;
  token2 = (TokenOperator  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL_STRING("+", token2->str);
  TEST_ASSERT_EQUAL(13, tokenizer->index);
  TEST_ASSERT_EQUAL(12, token2->startColumn);
  freeToken(token2);
  
  TokenInteger *token3 = NULL;
  token3 = (TokenInteger *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(15, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("67", token3->str);
  TEST_ASSERT_EQUAL(67, token3->value);
  TEST_ASSERT_EQUAL(13, token3->startColumn);
  freeToken(token3);
  

  TokenString *token = NULL;
  token = (TokenString  *)getStringToken(tokenizer);
  TEST_ASSERT_EQUAL(23, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("\"school\"", token->str);
  TEST_ASSERT_EQUAL(15, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_errorIndicator_given_identifier(){
  char  *linestr = errorIndicator(4, "    HELLO I AM ...");
  TEST_ASSERT_EQUAL_STRING("    ^~~~~", linestr);
}

void  test_errorIndicator1_given_identifier(){
  char  *linestr = errorIndicator(10, "    HELLO I AM ...");
  TEST_ASSERT_EQUAL_STRING("          ^", linestr);
}

void  test_errorIndicator1_given_string(){
  char  *linestr = errorIndicator(1, " \"THIS IS A STRING   ");
  TEST_ASSERT_EQUAL_STRING(" ^~~~~~~~~~~~~~~~~~~~", linestr);
}

void  test_errorIndicator1_given_identifier_and_string(){
  char  *linestr = errorIndicator(13, " HiHiHi1937  \"THIS IS A STRING   ");
  TEST_ASSERT_EQUAL_STRING("             ^~~~~~~~~~~~~~~~~~~~", linestr);
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