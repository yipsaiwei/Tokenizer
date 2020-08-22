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

void  test_createTokenizer_given_identifier_expect_same(){
  Tokenizer *tokenizer = createTokenizer(" Hihihi1038w");
  TEST_ASSERT_EQUAL_STRING(" Hihihi1038w", tokenizer->str);
  TEST_ASSERT_EQUAL(12, tokenizer->length);
  freeTokenizer(tokenizer);
}

void  test_tokenizerSkipSpaces_given_identifier_efnkfsl646_expect_the_same(){
  Tokenizer *tokenizer = createTokenizer("efnkfsl646"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING("efnkfsl646", str);
  TEST_ASSERT_EQUAL(0, tokenizer->index);
}

void  test_createTokenizer_given_numbers_identifiers_and_operator_expect_same(){
  Tokenizer *tokenizer = createTokenizer("39472 +1972 ajbdd qq");
  TEST_ASSERT_EQUAL_STRING("39472 +1972 ajbdd qq", tokenizer->str);
  TEST_ASSERT_EQUAL(20, tokenizer->length);
  freeTokenizer(tokenizer);
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


void  test_callThrowException_string(){
  char  *str = "  Hello \" Hello World ";
  char  *substr = "\" Hello World ";
  int   startColumn = 8;
  Try{
    callThrowException("Test Exception#1", str, startColumn, ERROR_INVALID_STRING);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_STRING_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_STRING, ex->errorCode);
    freeException(ex);   
  }    
}

void  test_callThrowException_decimal(){
  char  *str = "   4852   1864ab  sdjnvwoefg  ";
  char  *substr = "1864ab";
  int   startColumn = 10;
  Try{
    callThrowException("Test Exception#2", str, startColumn, ERROR_INVALID_INTEGER);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_STRING_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);   
  }    
}

void  test_callThrowException_operator(){
  char  *str = "  \"String here,,,,,\"  %  ";
  char  *substr = "%";
  int   startColumn = 22;
  Try{
    callThrowException("Test Exception#3", str, startColumn, ERROR_INVALID_OPERATOR);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_OPERATOR_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_OPERATOR, ex->errorCode);
    freeException(ex);   
  }    
}

void  test_errorIndicator_given_identifier(){
  char  *linestr = errorIndicator(4, "HELLO I AM ...");
  TEST_ASSERT_EQUAL_STRING("    ^~~~~", linestr);
}

void  test_errorIndicator1_given_identifier(){
  char  *linestr = errorIndicator(10, "HELLO I AM ...");
  TEST_ASSERT_EQUAL_STRING("          ^~~~~", linestr);
}

void  test_errorIndicator_given_string(){
  char  *linestr = errorIndicator(1, "\"THIS IS A STRING   ");
  TEST_ASSERT_EQUAL_STRING(" ^~~~~~~~~~~~~~~~~~~~", linestr);
}

void  test_errorIndicator1_given_identifier_and_string(){
  char  *linestr = errorIndicator(13, "HiHiHi1937  \"THIS IS A STRING   ");
  TEST_ASSERT_EQUAL_STRING("             ^~~~~~~~~~", linestr);
}

void  test_errorIndicator_given_numbers(){
  char  *linestr = errorIndicator(1, "135h31");
  TEST_ASSERT_EQUAL_STRING(" ^~~~~~", linestr);
}

void  test_errorIndicator_given_operator(){
  char  *linestr = errorIndicator(3, "+");
  TEST_ASSERT_EQUAL_STRING("   ^", linestr);
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

void  test_getDecimalToken_given_87bracket_expect_decimal_87(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  87("); 
  TokenInteger *token = NULL;
  token = getDecimalToken(tokenizer);
  TEST_ASSERT_EQUAL(4, tokenizer->index);
  TEST_ASSERT_EQUAL(2, token->length);
  TEST_ASSERT_EQUAL(87, token->value);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}


void  test_getDecimalToken_given_1a35_expect_exception_to_be_thrown(){
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

void  test_getDecimalToken_given_148o_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    148o   "); 
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

void  test_getOctalToken_given_063divide_expect_octal_63(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  063/"); 
  TokenInteger *token = NULL;
  token = getOctalToken(tokenizer);
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  TEST_ASSERT_EQUAL(063, token->value);
  TEST_ASSERT_EQUAL(2, token->startColumn);
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

void  test_getHexToken_given_0x999_and_Symbol_expect_0x999(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("     0x999&"); 
  TokenInteger *token = NULL;
  token = getHexToken(tokenizer);
  TEST_ASSERT_EQUAL(10, tokenizer->index);
  TEST_ASSERT_EQUAL(0x999, token->value);
  TEST_ASSERT_EQUAL(5, token->startColumn);
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

void  test_getFloatToken_given_256point_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  256."); 
  TokenFloat *token = NULL;
  token = getFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(256.0, token->value);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_66point191_or_symbol_expect_66point191(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("       66.191^"); 
  TokenFloat *token = NULL;
  token = getFloatToken(tokenizer);
  TEST_ASSERT_EQUAL(13, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(66.191, token->value);
  TEST_ASSERT_EQUAL(7, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_74point_e_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  74.e  3567"); /////////////////
  TokenFloat *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_101point191halo_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 101.191halo"); /////////////////
  TokenFloat *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
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

void  test_getFloatToken_given_19epoint5_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("19e.5"); 
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

void  test_getFloatToken_given_397point2y0_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("397.2y0"); 
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

void  test_getFloatToken_given_12point1eslash5_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("12.1e/5"); 
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

void  test_getBinToken_given_0b1011010remainder_expect_decimal_90(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("      0b1011010%"); 
  TokenInteger *token = NULL;
  token = getBinToken(tokenizer);
  TEST_ASSERT_EQUAL(15, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(90, token->value);
  TEST_ASSERT_EQUAL(6, token->startColumn);
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

void  test_getBinToken_given_0b11P0_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  0b11P0  "); 
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

void  test_getBinToken_given_0b10010plusplus_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    0b10010plusplus  "); 
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

void  test_getBinToken_given_0b0011_expect_decimal_3(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b0011"); 
  TokenInteger *token = NULL;
  token = getBinToken(tokenizer);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(3, token->value);
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

void  test_getIdentifierToken_given_calculate_this01c_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  calculate_this01c "); 
  TokenIdentifier *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(19, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("calculate_this01c", token->str);
  TEST_ASSERT_EQUAL(2, token->startColumn);
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

void  test_getIntegerOrFloatToken_given_54Q2_expect_exception_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 54Q2 "); 
  TokenInteger *token = NULL;
Try{
  token = (TokenInteger *)getIntegerOrFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getIntegerOrFloatToken_given_9point3ecomma2_expect_exception_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 9.3e,2 "); 
  TokenFloat *token = NULL;
Try{
  token = (TokenFloat *)getIntegerOrFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
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

void  test_getOperatorToken_given_multiply(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    * "); 
  TokenOperator *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("*", token->str);
  TEST_ASSERT_EQUAL(4, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_divide(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" / "); 
  TokenOperator *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("/", token->str);
  TEST_ASSERT_EQUAL(1, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_remainder(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" % "); 
  TokenOperator *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("%", token->str);
  TEST_ASSERT_EQUAL(1, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_AND(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("     &  "); 
  TokenOperator *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("&", token->str);
  TEST_ASSERT_EQUAL(5, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_OR(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   |  "); 
  TokenOperator *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(4, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("|", token->str);
  TEST_ASSERT_EQUAL(3, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getStringToken_Hello_how_are_you_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("\"Hello how are you  \""); 
  TokenString *token = NULL;
  token = (TokenString  *)getStringToken(tokenizer);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  TEST_ASSERT_EQUAL(21, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("\"Hello how are you  \"", token->str);
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
  tokenizer = createTokenizer("\"Hello how are you   "); 
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

void  test_getToken_given_plus_expect_getOperatorToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   +"); 
  TokenOperator *token = NULL;
  token = (TokenOperator  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(4, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("+", token->str);
  TEST_ASSERT_EQUAL(3, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getToken_given_minus_expect_getOperatorToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("     -  "); 
  TokenOperator *token = NULL;
  token = (TokenOperator  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("-", token->str);
  TEST_ASSERT_EQUAL(5, token->startColumn);
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

void  test_getToken_given_divide_expect_getOperatorToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" /   "); 
  TokenOperator *token = NULL;
  token = (TokenOperator  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("/", token->str);
  TEST_ASSERT_EQUAL(1, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getToken_given__vifhj_expect_getIdentifierToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    _vifhj+34"); 
  TokenIdentifier *token0 = NULL;
  token0 = (TokenIdentifier  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(IDENTIFIER_TYPE, token0->type);
  TEST_ASSERT_EQUAL(10, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("_vifhj", token0->str);
  TEST_ASSERT_EQUAL(4, token0->startColumn);
  freeToken(token0);
  
  TokenOperator *token1 = NULL;
  token1 = (TokenOperator  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(OPERATOR_TYPE, token1->type);
  TEST_ASSERT_EQUAL(11, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("+", token1->str);
  TEST_ASSERT_EQUAL(10, token1->startColumn);
  freeToken(token1);
  
  TokenInteger  *token2 = NULL;
  token2 = (TokenInteger  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(INTEGER_TYPE, token2->type);
  TEST_ASSERT_EQUAL(13, tokenizer->index);
  TEST_ASSERT_EQUAL(34, token2->value);
  TEST_ASSERT_EQUAL_STRING("34", token2->str);
  TEST_ASSERT_EQUAL(11, token2->startColumn);
  
  freeToken(token2);
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

void  test_getToken_given_a_string_and_some_numbers(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" \" A string  \"  12.3856e-2  12abc"); 
  TokenString *token0 = NULL;
  token0 = (TokenString  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(14, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("\" A string  \"", token0->str);
  TEST_ASSERT_EQUAL(1, token0->startColumn);
  freeToken(token0);
  
  TokenFloat *token1 = NULL;
  token1 = (TokenFloat  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(26, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("12.3856e-2", token1->str);
  TEST_ASSERT_EQUAL_FLOAT(12.3856e-2, token1->value);
  TEST_ASSERT_EQUAL(16, token1->startColumn);
  freeToken(token1);

  Try{
  TokenInteger  *token2 = NULL;
  token2 = getDecimalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_float_and_operator(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 56.395e-3+342 00x34"); 
  TokenFloat *token0 = NULL;
  token0 = (TokenFloat  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(10, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("56.395e-3", token0->str);
  TEST_ASSERT_EQUAL_FLOAT(56.395e-3, token0->value);
  TEST_ASSERT_EQUAL(1, token0->startColumn);
  freeToken(token0);
  
  TokenOperator *token1 = NULL;
  token1 = (TokenOperator *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(11, tokenizer->index);
  TEST_ASSERT_EQUAL(10, token1->startColumn);
  TEST_ASSERT_EQUAL_STRING("+", token1->str);
  freeToken(token1);

  TokenInteger *token2 = NULL;
  token2 = (TokenInteger *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(14, tokenizer->index);
  TEST_ASSERT_EQUAL(342, token2->value);
  TEST_ASSERT_EQUAL_STRING("342", token2->str);
  TEST_ASSERT_EQUAL(11, token2->startColumn);
  freeToken(token2);
  
  Try{
  TokenInteger  *token3 = NULL;
  token3 = getDecimalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_a_Identifier_and_number_and_operator(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" identi 0342af+3  28472fds"); 
  TokenIdentifier *token0 = NULL;
  token0 = (TokenIdentifier  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(7, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("identi", token0->str);
  TEST_ASSERT_EQUAL(1, token0->startColumn);
  freeToken(token0);
  

  Try{
  TokenInteger  *token1 = NULL;
  token1 = (TokenInteger  *)getToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_identifier_and_hex_and_operator_and_float(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" movwf 0x23+ 1.341e+4"); 
  TokenIdentifier *token0 = NULL;
  token0 = (TokenIdentifier  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("movwf", token0->str);
  TEST_ASSERT_EQUAL(1, token0->startColumn);
  freeToken(token0);
  
  TokenInteger *token1 = NULL;
  token1 = (TokenInteger *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(0x23, token1->value);
  TEST_ASSERT_EQUAL(11, tokenizer->index);
  TEST_ASSERT_EQUAL(7, token1->startColumn);
  TEST_ASSERT_EQUAL_STRING("0x23", token1->str);
  freeToken(token1);

  TokenOperator *token2 = NULL;
  token2 = (TokenOperator *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(12, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("+", token2->str);
  TEST_ASSERT_EQUAL(11, token2->startColumn);
  freeToken(token2);
  
  TokenFloat *token3 = NULL;
  token3 = (TokenFloat *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(21, tokenizer->index);
  TEST_ASSERT_EQUAL_FLOAT(1.341e+4, token3->value);
  TEST_ASSERT_EQUAL_STRING("1.341e+4", token3->str);
  TEST_ASSERT_EQUAL(13, token3->startColumn);
  freeToken(token3);
  
  freeTokenizer(tokenizer);
}

void  test_getToken_given_operator_and_number_and_string(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  + 12 \" String to test function       ");  
  TokenOperator *token0 = NULL;
  token0 = (TokenOperator  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(3, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("+", token0->str);
  TEST_ASSERT_EQUAL(2, token0->startColumn);
  freeToken(token0);
  
  TokenInteger *token1 = NULL;
  token1 = (TokenInteger *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(12, token1->value);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL(4, token1->startColumn);
  TEST_ASSERT_EQUAL_STRING("12", token1->str);
  freeToken(token1);

  Try{
  TokenString  *token1 = NULL;
  token1 = (TokenString  *) getToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_STRING_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_STRING, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

