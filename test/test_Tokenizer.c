#include "unity.h"
#include "Exception.h"
#include "CException.h"
#include "Tokenizer.h"
#include "Token.h"
#include <malloc.h> 
#include <stdarg.h>
#include  "DoubleLinkedList.h"
#include  "MemAlloc.h"

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

void  test_configureTokenizer_given_octal_bin_expect_config_12(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  123 + 12");
  configureTokenizer(tokenizer, TOKENIZER_OCT_O | TOKENIZER_BIN_B);
  TEST_ASSERT_EQUAL(12, tokenizer->config);
  freeTokenizer(tokenizer);
}

void  test_configureTokenizer_given_octal_bin_hex_dollar_sign_expect_config_15(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    hello  ");
  configureTokenizer(tokenizer, TOKENIZER_OCT_O | TOKENIZER_BIN_B | TOKENIZER_HEX_H | TOKENIZER_DOLLAR_SIGN_HEX);
  TEST_ASSERT_EQUAL(15, tokenizer->config);
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

void  test_tokenizerSkipSpaces_given_backslash_t(){
  Tokenizer *tokenizer = createTokenizer("\thellllllo"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING("hellllllo", str);
  TEST_ASSERT_EQUAL(1, tokenizer->index);
}

void  test_tokenizerSkipSpaces_given_backslash_n(){
  Tokenizer *tokenizer = createTokenizer("\nITEM"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING("ITEM", str);
  TEST_ASSERT_EQUAL(1, tokenizer->index);
}

void  test_tokenizerSkipSpaces_given_backslash_v(){
  Tokenizer *tokenizer = createTokenizer("\v BLOCK"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING("BLOCK", str);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
}

void  test_tokenizerSkipSpaces_given_backslash_f(){
  Tokenizer *tokenizer = createTokenizer("\f  GROUP"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING("GROUP", str);
  TEST_ASSERT_EQUAL(3, tokenizer->index);
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

void  test_duplicateSubString_2_given_a_number_and_length(){
  char  *str = "0x34847ADon't duplicate this!";
  char  *resultstr;
  resultstr = duplicateSubstring(str, 8);
  TEST_ASSERT_EQUAL_STRING("0x34847A", resultstr);
}


void  test_callThrowException_string(){
  char  *str = "  Hello \" Hello World ";
  char  *substr = "\" Hello World ";
  int   startColumn = 8;
  Try{
    callThrowException("Test Exception#1", str, startColumn, ERROR_TESTING);
    TEST_FAIL_MESSAGE("EXPECT ERROR_TESTING_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_TESTING, ex->errorCode);
    freeException(ex);   
  }    
}

void  test_callThrowException_decimal(){
  char  *str = "   4852   1864ab  sdjnvwoefg  ";
  char  *substr = "1864ab";
  int   startColumn = 10;
  Try{
    callThrowException("Test Exception#2", str, startColumn, ERROR_TESTING);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_STRING_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_TESTING, ex->errorCode);
    freeException(ex);   
  }    
}

void  test_callThrowException_operator(){
  char  *str = "  \"String here,,,,,\"  %  ";
  char  *substr = "%";
  int   startColumn = 22;
  Try{
    callThrowException("Test Exception#3", str, startColumn, ERROR_TESTING);
    TEST_FAIL_MESSAGE("EXPECT ERROR_TESTING_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_TESTING, ex->errorCode);
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
  Try{
    token = getDecimalToken(tokenizer);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL(3, token->length);
    TEST_ASSERT_EQUAL(351, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalToken_given_87bracket_expect_decimal_87(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  87("); 
  TokenInteger *token = NULL;
  Try{
    token = getDecimalToken(tokenizer);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL(2, token->length);
    TEST_ASSERT_EQUAL(87, token->value);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalToken_given_873Ah_without_hex_config_expect_exception_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  873Ah"); 
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

void  test_getDecimalToken_given_873Ah_with_hex_config_expect_hexadecimal_0x873A(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  873Ah  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  TokenInteger *token = NULL;
  Try{
    token = getDecimalToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(0x873A, token->value);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalToken_given_D43Ah_plus_with_hex_config_expect_hexadecimal_0xD43A(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   D43Ah+  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  TokenInteger *token = NULL;
  Try{
    token = getDecimalToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(0xD43A, token->value);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalToken_given_ABCDH_with_hex_config_expect_hexadecimal_34723(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    ABCDH  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  TokenInteger *token = NULL;
  Try{
    token = getDecimalToken(tokenizer);
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(0xABCD, token->value);
    TEST_ASSERT_EQUAL(4, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalToken_given_52__with_hex_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  10E3h_"); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
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

void  test_getDecimalToken_given_10E3h653__with_hex_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  10E3h653"); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
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

void  test_getDecimalToken_given_FDECHell__with_hex_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" FDECHell"); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
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

void  test_getDecimalToken_given_10001b_without_bin_config_expect_exception_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   10001b "); 
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

void  test_getDecimalToken_given_10110b_with_bin_config_expect_bin_10110(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    10110b  "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  TokenInteger *token = NULL;
  Try{
    token = getDecimalToken(tokenizer);
    TEST_ASSERT_EQUAL(10, tokenizer->index);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(0b10110, token->value);
    TEST_ASSERT_EQUAL(4, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalToken_given_101B_with_bin_config_expect_bin_101(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  101B  "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  TokenInteger *token = NULL;
  Try{
    token = getDecimalToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(0b101, token->value);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalToken_given_10101b_minus_with_bin_config_expect_bin_10101(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  10101b-  "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  TokenInteger *token = NULL;
  Try{
    token = getDecimalToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(0b10101, token->value);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalToken_given_10101b__with_bin_config_expect_bin_1100(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  1100b _  "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  TokenInteger *token = NULL;
  Try{
    token = getDecimalToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(0b1100, token->value);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalToken_given_10111b_hello__with_bin_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 10111b_hello"); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
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

void  test_getDecimalToken_given_11111b43_hello__with_bin_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  11111b43"); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
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

void  test_getDecimalToken_given_134o_without_oct_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  134o "); 
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

void  test_getDecimalToken_given_134o_with_oct_config_expect_oct_134(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   134o "); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  TokenInteger *token = NULL;
  Try{
    token = getDecimalToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(0134, token->value);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalToken_given_413O_with_oct_config_expect_oct_413(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   413O "); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  TokenInteger *token = NULL;
  Try{
    token = getDecimalToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(0413, token->value);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalToken_given_3945o_with_oct_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  3945o "); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
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

void  test_getDecimalToken_given_12o_hello_with_oct_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  12o_hello "); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
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

void  test_getDecimalToken_given_78wxy_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  78wxy@"); 
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
  Try{
    token = getOctalToken(tokenizer);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL(035, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getOctalToken_given_063divide_expect_octal_63(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  063/"); 
  TokenInteger *token = NULL;
  Try{
    token = getOctalToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(063, token->value);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
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

void  test_getOctalToken_given_085o_with_oct_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  085o "); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
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
  Try{
    token = getHexToken(tokenizer);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL(0x55, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getHexToken_given_0x999_and_Symbol_expect_0x999(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("     0x999&"); 
  TokenInteger *token = NULL;
  Try{
    token = getHexToken(tokenizer);
    TEST_ASSERT_EQUAL(10, tokenizer->index);
    TEST_ASSERT_EQUAL(0x999, token->value);
    TEST_ASSERT_EQUAL(5, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
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
  Try{
    token = getHexToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(0xface, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
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

void  test_getHexToken_given_0xC34Ah_with_hex_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   0xC34Ah  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
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
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(1.456, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_256point_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  256."); 
  TokenFloat *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(256., token->value);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_66point191_or_symbol_expect_66point191(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("       66.191^"); 
  TokenFloat *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(13, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(66.191, token->value);
    TEST_ASSERT_EQUAL(7, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
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
  tokenizer = createTokenizer(" 101.191halo");
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
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(3.836e2, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_7pointe2_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  7.e2"); 
  TokenFloat *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(7.e2, token->value);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_e2_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0.e2"); 
  TokenFloat *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(0.e2, token->value);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}
  
void  test_getFloatToken_given_53point12eplus2_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("53.12e+2"); 
  TokenFloat *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(53.12e+2, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_18356point123eminus4_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("18356.123e-4"); 
  TokenFloat *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(18356.123e-4, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_186point13minus4_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("186.13-4"); 
  TokenFloat *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(186.13, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_1point034eplus3plus12_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1.034e+3+12"); 
  TokenFloat *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(1.034e+3, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
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

void  test_getFloatToken_given_654e_minus2_abc_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   654e-2_abc /3  "); 
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

void  test_getFloatToken_given_12point4point4point2point_e_minus_minus_4_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("     12.4.4.2.e--4         "); 
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


void  test_getFloatToken_given_81point3eplusq_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  81.3e+q  "); 
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
  Try{
    token = getBinToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(6, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getBinToken_given_0b1111_expect_decimal_15(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b1111"); 
  TokenInteger *token = NULL;
  Try{
    token = getBinToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(15, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getBinToken_given_0b1011010remainder_expect_decimal_90(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("      0b1011010%"); 
  TokenInteger  *token = NULL;
  Try{
    token = getBinToken(tokenizer);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(90, token->value);
    TEST_ASSERT_EQUAL(6, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
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

void  test_getBinToken_given_0b0011b_with_bin_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    0b0011b  "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
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

void  test_getIdentifierToken_given_Iden913__minus0x13_expect_without_plus(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  _Iden913__-0x13 "); 
  TokenIdentifier *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(12, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("_Iden913__", token->str);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
}


void  test_getNumberToken_given_375_expect_getDecimalToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("375"); 
  TokenInteger *token = NULL;
  Try{
    token = (TokenInteger *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL(375, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}


void  test_getNumberToken_given_87point9234_expect_getFloatToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("87.9234"); 
  TokenFloat *token = NULL;
  Try{
    token = (TokenFloat *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(87.9234, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getNumberToken_given_93point_e_minus2_expect_getFloatToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   93.e-2  "); 
  TokenFloat *token = NULL;
  Try{
    token = (TokenFloat *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    TEST_ASSERT_EQUAL(93.e-2, token->value);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getNumberToken_given_0x9521_expect_getHexToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0x9521"); 
  TokenInteger *token = NULL;
  Try{
    token = (TokenInteger *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(0x9521, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getNumberToken_given_0b1010_expect_getHexToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b1010"); 
  TokenInteger *token = NULL;
  Try{
    token = (TokenInteger *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(0b1010, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getNumberToken_given_0345_expect_getOctToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0345"); 
  TokenInteger *token = NULL;
  Try{
    token = (TokenInteger *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL(0345, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getNumberToken_given_0139_expect_getIntegerToken_called_exception_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    0139"); 
  TokenFloat *token = NULL;
  Try{
  token = (TokenFloat *)getNumberToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
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

void  test_getNumberToken_given_34point_e_excalmation_1_expect_getFloatToken_called_exception_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  34.e!1 "); 
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

void  test_getNumberToken_given_54b_expect_getIntegerToken_called_exception_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  54b"); 
  TokenFloat *token = NULL;
  Try{
  token = (TokenFloat *)getNumberToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
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

void  test_getNumberToken_given_0345_12point3e2_12_0x123_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0345 12.3e2 12 0x123"); 
  TokenInteger *token0 = NULL;
  Try{
    token0 = (TokenInteger *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(0345, token0->value);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
    TokenFloat  *token1 = NULL;
    token1 = (TokenFloat  *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(12.3e2, token1->value);
    TEST_ASSERT_EQUAL(6, token1->startColumn);
    freeToken(token1);
  
    TokenInteger *token2 = NULL;
    token2 = (TokenInteger *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL(12, token2->value);
    TEST_ASSERT_EQUAL(13, token2->startColumn);
    freeToken(token2);
  
    TokenInteger *token3 = NULL;
    token3 = (TokenInteger *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(21, tokenizer->index);
    TEST_ASSERT_EQUAL(0x123, token3->value);
    TEST_ASSERT_EQUAL(16, token3->startColumn);
    freeToken(token3);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getNumberToken_given_0x123_456_32point_e_plus_minus_2_expect_getOctToken_called_exception_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0x123 456 32.e+-2 0b1010"); 
  TokenInteger *token0 = NULL;
  Try{
  token0 = (TokenInteger *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL(0x123, token0->value);
  TEST_ASSERT_EQUAL(1, token0->startColumn);
  freeToken(token0);
  
  TokenInteger *token1 = NULL;
  token1 = (TokenInteger *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(10, tokenizer->index);
  TEST_ASSERT_EQUAL(456, token1->value);
  TEST_ASSERT_EQUAL(7, token1->startColumn);
  freeToken(token1);
  
  TokenFloat *token2 = NULL;
  token2 = (TokenFloat *)getNumberToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getIntegerOrFloatToken_given_138point1874_expect_getFloatToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   138.1874"); 
  TokenFloat *token = NULL;
  Try{
    token = (TokenFloat *)getIntegerOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(138.1874, token->value);
    TEST_ASSERT_EQUAL(11, tokenizer->index);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getIntegerOrFloatToken_given_87e2_expect_getFloatToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  87e2"); 
  TokenFloat *token = NULL;
  Try{
    token = (TokenFloat *)getIntegerOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(87e2, token->value);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getIntegerOrFloatToken_given_927point34e_minus2_expect_getFloatToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  927.34e-2  "); 
  TokenFloat *token = NULL;
  Try{
    token = (TokenFloat *)getIntegerOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(927.34e-2, token->value);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    TEST_ASSERT_EQUAL(11, tokenizer->index);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getIntegerOrFloatToken_given_4532_expect_getIntegerToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 4532"); 
  TokenInteger *token = NULL;
  Try{
    token = (TokenInteger *)getIntegerOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(4532, token->value);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
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

void  test_getIntegerOrFloatToken_given_9point_slash123_expect_exception_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 9.4.1.2.3 "); 
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

void  test_getIntegerOrFloatToken_given_9point_e_plus_plus_2_expect_exception_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 9.e++2 "); 
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

void  test_getIntegerOrFloatToken_given_9point3e_comma2_expect_exception_thrown(){
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

void  test_getIntegerOrFloatToken_given_382point464e_plus1_18372_expect_getFloatToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  382.464e+1 18372   "); 
  TokenFloat *token0 = NULL;
  Try{
    token0 = (TokenFloat *)getIntegerOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(FLOAT_TYPE, token0->type);
    TEST_ASSERT_EQUAL_FLOAT(382.464e+1, token0->value);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    freeToken(token0);
  
    TokenInteger *token1 = NULL;
    token1 = (TokenInteger *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(18, tokenizer->index);
    TEST_ASSERT_EQUAL(18372, token1->value);
    TEST_ASSERT_EQUAL(13, token1->startColumn);
    freeToken(token1);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
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

void  test_getOperatorToken_given_parentheses_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("     (  "); 
  TokenOperator *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("(", token->str);
  TEST_ASSERT_EQUAL(5, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_braces_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  {  "); 
  TokenOperator *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(3, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("{", token->str);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_square_bracket_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" [  "); 
  TokenOperator *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("[", token->str);
  TEST_ASSERT_EQUAL(1, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 



void  test_getStringToken_Hello_how_are_you_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("\"Hello how are you  \""); 
  TokenString *token = NULL;
  Try{
    token = (TokenString  *)getStringToken(tokenizer);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    TEST_ASSERT_EQUAL(21, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("\"Hello how are you  \"", token->str);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");       
  }
}

void  test_getStringToken_hi_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("\"hi\""); 
  TokenString *token = NULL;
  Try{
    token = (TokenString  *)getStringToken(tokenizer);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("\"hi\"", token->str);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");       
  }
}

void  test_getStringToken_This_is_a_string_to_test_this_function_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  \"This is a string to test this function.\"   "); 
  TokenString *token = NULL;
  Try{
    token = (TokenString  *)getStringToken(tokenizer);
    TEST_ASSERT_EQUAL(43, tokenizer->index);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    TEST_ASSERT_EQUAL_STRING("\"This is a string to test this function.\"", token->str);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}


void  test_getStringToken_Hello_comma_abcdeQf_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  \"Hello, abcde?f\" "); 
  TokenString *token = NULL;
  Try{
    token = (TokenString  *)getStringToken(tokenizer);
    TEST_ASSERT_EQUAL(18, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("\"Hello, abcde?f\"", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");         
  }
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

  void  test_getToken_given_NULL_expect_NULL_token_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("      "); 
  Token *token = NULL;
  Try{
    token = getToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(NULL_TYPE, token->type);
    TEST_ASSERT_EQUAL(6, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");       
  }
}

void  test_getToken_given_hello123_expect_getIdentifierToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("hello123"); 
  TokenIdentifier *token = NULL;
  Try{
    token = (TokenIdentifier  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(IDENTIFIER_TYPE, token->type);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("hello123", token->str);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");   
  }
}

void  test_getToken_given_197e2_expect_getFloatToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  197e2  "); 
  TokenFloat *token = NULL;
  Try{
    token = (TokenFloat  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(197e2, token->value);
    TEST_ASSERT_EQUAL_STRING("197e2", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");   
  }
}

void  test_getToken_given_6135_expect_getDecimalToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  6135 "); 
  TokenInteger *token = NULL;
  Try{
    token = (TokenInteger *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(6135, token->value);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
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
  Try{
    token = (TokenInteger  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(23, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}


void  test_getToken_given_plus_expect_getOperatorToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   +"); 
  TokenOperator *token = NULL;
  Try{
    token = (TokenOperator  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("+", token->str);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getToken_given_minus_expect_getOperatorToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("     -  "); 
  TokenOperator *token = NULL;
  Try{
    token = (TokenOperator  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("-", token->str);
    TEST_ASSERT_EQUAL(5, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");  
  }
}

void  test_getToken_given_multiply_expect_getOperatorToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("     *"); 
  TokenOperator *token = NULL;
  Try{
    token = (TokenOperator  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("*", token->str);
    TEST_ASSERT_EQUAL(5, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getToken_given_divide_expect_getOperatorToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" /   "); 
  TokenOperator *token = NULL;
  Try{
    token = (TokenOperator  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(2, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("/", token->str);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given__vifhj_expect_getIdentifierToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    _vifhj+34"); 
  TokenIdentifier *token0 = NULL;
  Try{
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
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}


void  test_getToken_given_spacex3wxyplus_expect_getIdentifierToken_getOperatorToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   wxy+"); 
  TokenIdentifier *token0 = NULL;
  Try{
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
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}


void  test_getToken_given_spacex3wxyplus_expect_getHexToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0x349f hello+312-4"); 
  TokenInteger *token0 = NULL;
  Try{
    token0 = (TokenInteger  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("0x349f", token0->str);
    TEST_ASSERT_EQUAL(0x349f, token0->value);
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
  
    TokenOperator *token5 = NULL;
    token5 = (TokenOperator  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL_STRING("-", token5->str);
    TEST_ASSERT_EQUAL(18, tokenizer->index);
    TEST_ASSERT_EQUAL(17, token5->startColumn);
    freeToken(token5);
  
    TokenInteger *token6 = NULL;
    token6 = (TokenInteger *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(19, tokenizer->index);
    TEST_ASSERT_EQUAL(4, token6->value);
    TEST_ASSERT_EQUAL(18, token6->startColumn);
    freeToken(token6);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given_1947_divide_34point32e_minus2_times_034_minus_0x12_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   1947/34.32e-2*034-0x12"); 
  TokenInteger *token0 = NULL;
  Try{
    token0 = (TokenInteger  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("1947", token0->str);
    TEST_ASSERT_EQUAL(1947, token0->value);
    TEST_ASSERT_EQUAL(3, token0->startColumn);
    freeToken(token0);
  
    TokenOperator *token1 = NULL;
    token1 = (TokenOperator  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("/", token1->str);
    TEST_ASSERT_EQUAL(7, token1->startColumn);
    freeToken(token1);
  
    TokenFloat *token2 = NULL;
    token2 = (TokenFloat  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(16, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("34.32e-2", token2->str);
    TEST_ASSERT_EQUAL(34.32e-2, token2->value);
    TEST_ASSERT_EQUAL(8, token2->startColumn);
    freeToken(token2);
  
    TokenOperator *token3 = NULL;
    token3 = (TokenOperator  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(17, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("*", token3->str);
    TEST_ASSERT_EQUAL(16, token3->startColumn);
    freeToken(token3);
  
    TokenInteger *token4 = NULL;
    token4 = (TokenInteger  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(20, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("034", token4->str);
    TEST_ASSERT_EQUAL(034, token4->value);
    TEST_ASSERT_EQUAL(17, token4->startColumn);
    freeToken(token4);
  
    TokenOperator *token5 = NULL;
    token5 = (TokenOperator  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(21, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("-", token5->str);
    TEST_ASSERT_EQUAL(20, token5->startColumn);
    freeToken(token5);
  
    TokenInteger *token6 = NULL;
    token6 = (TokenInteger  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(25, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("0x12", token6->str);
    TEST_ASSERT_EQUAL(0x12, token6->value);
    TEST_ASSERT_EQUAL(21, token6->startColumn);
    freeToken(token4);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given_bracket_Identi183__minus0x13_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  (_Identi183__-0x13 "); 
  TokenOperator *token0 = NULL;
  Try{
    token0 = (TokenOperator  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("(", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
  
    TokenIdentifier *token1 = NULL;
    token1 = (TokenIdentifier  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("_Identi183__", token1->str);
    TEST_ASSERT_EQUAL(3, token1->startColumn);
    freeToken(token1);
  
    TokenOperator *token2 = NULL;
    token2 = (TokenOperator  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(16, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("-", token2->str);
    TEST_ASSERT_EQUAL(15, token2->startColumn);
    freeToken(token2);
  
    TokenInteger *token3 = NULL;
    token3 = (TokenInteger  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(20, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("0x13", token3->str);
    TEST_ASSERT_EQUAL(0x13, token3->value);
    TEST_ASSERT_EQUAL(16, token3->startColumn);
    freeToken(token3);
  
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}
  
  
void  test_getToken_given_String_033_plus_hello_expect_getHexToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" \"String Here\"033+hello"); 
  TokenString *token0 = NULL;
  Try{
    token0 = (TokenString  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("\"String Here\"", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
    TokenInteger  *token1 = NULL;
    token1 = (TokenInteger  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(17, tokenizer->index);
    TEST_ASSERT_EQUAL(033, token1->value);
    TEST_ASSERT_EQUAL_STRING("033", token1->str);
    TEST_ASSERT_EQUAL(14, token1->startColumn);
    freeToken(token1);
  
    TokenOperator *token2 = NULL;
    token2 = (TokenOperator *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(18, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("+", token2->str);
    TEST_ASSERT_EQUAL(17, token2->startColumn);
    freeToken(token2);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given_Peace_123plus67_expect_getHexToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  Peace  123+67\"school\""); 
  TokenIdentifier *token0 = NULL;
  Try{
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
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given_a_string_float_and_invalid_identifier_expect_exception_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" \" A string  \"  12.3856e-2  12abc"); 
  TokenString *token0 = NULL;
  Try{
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

void  test_getToken_given_float_and_operator_and_invalid_hex_expect_exception_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 56.395e-3+342 00x34"); 
  TokenFloat *token0 = NULL;
  Try{
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
  Try{
    token0 = (TokenIdentifier  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("identi", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
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
  Try{
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
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given__identifier_float_and_operator(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   _accelerator_ 148.1323346423e-2/"); 
  TokenIdentifier *token0 = NULL;
  Try{
    token0 = (TokenIdentifier  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(16, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("_accelerator_", token0->str);
    TEST_ASSERT_EQUAL(3, token0->startColumn);
    freeToken(token0);
  
    TokenFloat *token1 = NULL;
    token1 = (TokenFloat *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(34, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(148.1323346423e-2, token1->value);
    TEST_ASSERT_EQUAL_STRING("148.1323346423e-2", token1->str);
    TEST_ASSERT_EQUAL(17, token1->startColumn);
    freeToken(token1);
  
    TokenOperator *token3 = NULL;
    token3 = (TokenOperator *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(35, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("/", token3->str);
    TEST_ASSERT_EQUAL(34, token3->startColumn);
    freeToken(token3);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown."); 
  }
  
}

void  test_getToken_given_operator_and_number_and_string(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  + 12 \" String to test function       ");  
  TokenOperator *token0 = NULL;
  Try{
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

    TokenString  *token2 = NULL;
    token2 = (TokenString  *) getToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_STRING_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_STRING, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_operator_and_invalid_float_and_octal_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  *18.e0x12 066  ");  
  TokenOperator *token0 = NULL;
  Try{
    token0 = (TokenOperator  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("*", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
  
    TokenFloat  *token1 = NULL;
    token1 = (TokenFloat  *) getToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
  
}

void  test_getToken_given_operator_and_indentifier_and_string(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  .POINT\"A string @183\" ");  
  TokenOperator *token0 = NULL;
  Try{
    token0 = (TokenOperator  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING(".", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
  
    TokenIdentifier *token1 = NULL;
    token1 = (TokenIdentifier  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(IDENTIFIER_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("POINT", token1->str);
    TEST_ASSERT_EQUAL(3, token1->startColumn);
    freeToken(token1);
  
    TokenString *token2 = NULL;
    token2 = (TokenString *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(23, tokenizer->index);
    TEST_ASSERT_EQUAL(STRING_TYPE, token2->type);
    TEST_ASSERT_EQUAL_STRING("\"A string @183\"", token2->str);
    TEST_ASSERT_EQUAL(8, token2->startColumn);
    freeToken(token2);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
  
}


void  test_duplicateToken(){
  TokenIdentifier *token = NULL;
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" aStringHere @0183 ");  
  token = (TokenIdentifier  *)getToken(tokenizer);
  TEST_ASSERT_EQUAL(12, tokenizer->index);
  TEST_ASSERT_EQUAL(IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL_STRING("aStringHere", token->str);
  TEST_ASSERT_EQUAL(1, token->startColumn);
  TEST_ASSERT_EQUAL(11, token->length);
  
  Token *newToken = duplicateToken((Token *)token);
  TEST_ASSERT_EQUAL(IDENTIFIER_TYPE, newToken->type);
  TEST_ASSERT_EQUAL_STRING("aStringHere", newToken->str);
  TEST_ASSERT_EQUAL(1, newToken->startColumn);
  TEST_ASSERT_EQUAL(11, newToken->length);
  
  freeToken(newToken);
  freeToken(token);
  freeTokenizer(tokenizer);
}


void  test_pushBackToken_given_decimal(){
  TokenInteger *token = NULL;
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   0263   "); 
  Try{
    token = (TokenInteger  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("0263", token->str);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    TEST_ASSERT_EQUAL(4, token->length);
  
    pushBackToken(tokenizer, (Token *)token);     // Push the token back to tokenizer
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token, ((Token  *)(tokenizer->list->head->data)));
    TEST_ASSERT_EQUAL_STRING("0263", ((Token  *)(tokenizer->list->head->data))->str);
  
    token = (TokenInteger  *)getToken(tokenizer);   //Pop the token from tokenizer
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("0263", token->str);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    TEST_ASSERT_EQUAL(4, token->length);
    free(token);
    freeTokenizer(tokenizer);   //token will be freed in list also
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}


/*
list            item3     item2     item1     
head ---------->next----->next----->next-----------
tail----   |----prev<-----prev<-----prev           |
count  |   |     token2    token1   token0        NULL
       |  NULL                         ^
       |_______________________________|
*/


void  test_pushBackToken_given_decimal_float_identifier(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  1934 3e-2 HIHI   ");  
  TokenInteger  *token0 = NULL;
  Try{
    token0 = (TokenInteger  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(1934, token0->value);
    TEST_ASSERT_EQUAL_STRING("1934", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token0);             //push back token here
    TEST_ASSERT_EQUAL(2, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("1934", ((Token  *)(tokenizer->list->head->data))->str);
    TEST_ASSERT_EQUAL_PTR(NULL, tokenizer->list->head->prev);
    TEST_ASSERT_EQUAL_PTR(NULL, tokenizer->list->head->next);
    TEST_ASSERT_EQUAL(2, ((Token *)(tokenizer->list->head->data))->startColumn);
    TEST_ASSERT_EQUAL(INTEGER_TYPE, ((Token  *)(tokenizer->list->head->data))->type);
  
    token0 = (TokenInteger  *)getToken(tokenizer);        //get back same token
    TEST_ASSERT_EQUAL(INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(1934, token0->value);
    TEST_ASSERT_EQUAL_STRING("1934", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
  
    TokenFloat  *token1 = NULL;
    token1 = (TokenFloat  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(11, tokenizer->index);
    TEST_ASSERT_EQUAL(FLOAT_TYPE, token1->type);
    TEST_ASSERT_EQUAL_FLOAT(3e-2, token1->value);
    TEST_ASSERT_EQUAL_STRING("3e-2", token1->str);
    TEST_ASSERT_EQUAL(7, token1->startColumn);
   
    pushBackToken(tokenizer,(Token  *) token1);          //push back token here
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("3e-2", ((Token  *)(tokenizer->list->head->data))->str);
    TEST_ASSERT_EQUAL_STRING("3e-2", ((Token  *)(tokenizer->list->tail->data))->str);
  
    token1 = (TokenFloat  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(11, tokenizer->index);
    TEST_ASSERT_EQUAL(FLOAT_TYPE, token1->type);
    TEST_ASSERT_EQUAL_FLOAT(3e-2, token1->value);
    TEST_ASSERT_EQUAL_STRING("3e-2", token1->str);
    TEST_ASSERT_EQUAL(7, token1->startColumn);
    freeToken(token1);
  
    TokenIdentifier *token2 = NULL;
    token2 = (TokenIdentifier  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(16, tokenizer->index);
    TEST_ASSERT_EQUAL(IDENTIFIER_TYPE, token2->type);
    TEST_ASSERT_EQUAL_STRING("HIHI", token2->str);
    TEST_ASSERT_EQUAL(12, token2->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token2);       //push back token here
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("HIHI", ((Token  *)(tokenizer->list->head->data))->str);
    TEST_ASSERT_EQUAL_STRING("HIHI", ((Token  *)(tokenizer->list->tail->data))->str);
  
    token2 = (TokenIdentifier  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(16, tokenizer->index);
    TEST_ASSERT_EQUAL(IDENTIFIER_TYPE, token2->type);
    TEST_ASSERT_EQUAL_STRING("HIHI", token2->str);
    TEST_ASSERT_EQUAL(12, token2->startColumn);
    freeToken(token2);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}


void  test_pushBackToken_given_2_continuous_pushbacks(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 123*   ");
  TokenInteger  *token0 = NULL;
  TokenOperator *token1 = NULL;
  Try{
    token0 = (TokenInteger  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL(123, token0->value);
    TEST_ASSERT_EQUAL_STRING("123", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
  
    token1 = (TokenOperator *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("*", token1->str);
    TEST_ASSERT_EQUAL(4, token1->startColumn);
  
    pushBackToken(tokenizer, (Token *)token1);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->head->data);
    pushBackToken(tokenizer, (Token*)token0);
    TEST_ASSERT_EQUAL(1, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token0, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->tail->data);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_pushBackToken_given_5_continuous_pushbacks(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" Hello123 0132/1.34e33\"StringHere.Stop\" ");
  TokenIdentifier  *token0 = NULL;
  TokenInteger *token1 = NULL;
  TokenOperator *token2 = NULL;
  TokenFloat  *token3 = NULL;
  TokenString *token4 = NULL;
  
  Try{
    token0 = (TokenIdentifier  *)getToken(tokenizer);   //Obtain token
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("Hello123", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
  
    token1 = (TokenInteger *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL(0132, token1->value);
    TEST_ASSERT_EQUAL_STRING("0132", token1->str);
    TEST_ASSERT_EQUAL(10, token1->startColumn);
  
    token2 = (TokenOperator *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("/", token2->str);
    TEST_ASSERT_EQUAL(14, token2->startColumn);
  
    token3 = (TokenFloat  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(22, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(1.34e33, token3->value);
    TEST_ASSERT_EQUAL_STRING("1.34e33", token3->str);
    TEST_ASSERT_EQUAL(15, token3->startColumn);
  
    token4 = (TokenString *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(39, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("\"StringHere.Stop\"", token4->str);
    TEST_ASSERT_EQUAL(22, token4->startColumn);

    pushBackToken(tokenizer, (Token *)token4);    //push back tokens one by one
    TEST_ASSERT_EQUAL(22, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token4, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token4, tokenizer->list->tail->data);
    pushBackToken(tokenizer, (Token *)token3);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token3, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token4, tokenizer->list->tail->data);
    pushBackToken(tokenizer, (Token *)token2);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token2, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token3, tokenizer->list->head->next->data);
    TEST_ASSERT_EQUAL_PTR(token3, tokenizer->list->tail->prev->data);
    TEST_ASSERT_EQUAL_PTR(token4, tokenizer->list->tail->data);
    pushBackToken(tokenizer, (Token *)token1);
    TEST_ASSERT_EQUAL(10, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token2, tokenizer->list->head->next->data);
    TEST_ASSERT_EQUAL_PTR(token3, tokenizer->list->head->next->next->data);
    TEST_ASSERT_EQUAL_PTR(token4, tokenizer->list->head->next->next->next->data);
    TEST_ASSERT_EQUAL_PTR(token4, tokenizer->list->tail->data);
    TEST_ASSERT_EQUAL_PTR(token3, tokenizer->list->tail->prev->data);
    TEST_ASSERT_EQUAL_PTR(token2, tokenizer->list->tail->prev->prev->data);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->tail->prev->prev->prev->data);
    pushBackToken(tokenizer, (Token *)token0);
    TEST_ASSERT_EQUAL(1, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token0, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->head->next->data);
    TEST_ASSERT_EQUAL_PTR(token2, tokenizer->list->head->next->next->data);
    TEST_ASSERT_EQUAL_PTR(token3, tokenizer->list->head->next->next->next->data);
    TEST_ASSERT_EQUAL_PTR(token4, tokenizer->list->head->next->next->next->next->data);
    TEST_ASSERT_EQUAL_PTR(token4, tokenizer->list->tail->data);
    TEST_ASSERT_EQUAL_PTR(token3, tokenizer->list->tail->prev->data);
    TEST_ASSERT_EQUAL_PTR(token2, tokenizer->list->tail->prev->prev->data);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->tail->prev->prev->prev->data);
    TEST_ASSERT_EQUAL_PTR(token0, tokenizer->list->tail->prev->prev->prev->prev->data);
  
    token0 = (TokenIdentifier  *)getToken(tokenizer);   //pop pushed tokens
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("Hello123", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
    token1 = (TokenInteger *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL(0132, token1->value);
    TEST_ASSERT_EQUAL_STRING("0132", token1->str);
    TEST_ASSERT_EQUAL(10, token1->startColumn);
    freeToken(token1);
  
    token2 = (TokenOperator *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("/", token2->str);
    TEST_ASSERT_EQUAL(14, token2->startColumn);
    freeToken(token2);
  
    token3 = (TokenFloat  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(22, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(1.34e33, token3->value);
    TEST_ASSERT_EQUAL_STRING("1.34e33", token3->str);
    TEST_ASSERT_EQUAL(15, token3->startColumn);
    freeToken(token3);
  
    token4 = (TokenString *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(39, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("\"StringHere.Stop\"", token4->str);
    TEST_ASSERT_EQUAL(22, token4->startColumn);
    freeToken(token4);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}


void  test_pushBackToken_given_octal_string_operator(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0231 \"STRING here 1202\" % ");  
  TokenInteger  *token0 = NULL;
  Token *tokenptr = NULL;
  Try{
    token0 = (TokenInteger  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(0231, token0->value);
    TEST_ASSERT_EQUAL_STRING("0231", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
 
    pushBackToken(tokenizer,(Token  *) token0);
    TEST_ASSERT_EQUAL(1, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token0, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token0, tokenizer->list->tail->data);

    token0 = (TokenInteger  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(0231, token0->value);
    TEST_ASSERT_EQUAL_STRING("0231", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
    TokenString *token1 = NULL;
    token1 = (TokenString *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(24, tokenizer->index);
    TEST_ASSERT_EQUAL(STRING_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("\"STRING here 1202\"", token1->str);
    TEST_ASSERT_EQUAL(6, token1->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token1);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->tail->data);
  
    token1 = (TokenString *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(24, tokenizer->index);
    TEST_ASSERT_EQUAL(STRING_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("\"STRING here 1202\"", token1->str);
    TEST_ASSERT_EQUAL(6, token1->startColumn);
    freeToken(token1);
  
    TokenOperator *token2 = NULL;
    token2 = (TokenOperator *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(26, tokenizer->index);
    TEST_ASSERT_EQUAL(OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL_STRING("%", token2->str);
    TEST_ASSERT_EQUAL(25, token2->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token2);
    TEST_ASSERT_EQUAL(25, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token2, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token2, tokenizer->list->tail->data);
  
    token2 = (TokenOperator *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(26, tokenizer->index);
    TEST_ASSERT_EQUAL(OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL_STRING("%", token2->str);
    TEST_ASSERT_EQUAL(25, token2->startColumn);
    freeToken(token2);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}


/*
list        item5   item4     item3     item2     item1     
head------->next---->next---->next----->next----->next---------
tail----    prev<----prev<----prev<-----prev<-----prev        |
count  |    token4   token3   token2    token1    token0    NULL
       |                                            ^
       |____________________________________________|
*/


void  test_pushBackToken_given_hexa_operator_float_operator_identifier(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0x19E3/12.e-2*index ");  
  TokenInteger  *token0 = NULL;
  Token *tokenptr = NULL;
  Try{
    token0 = (TokenInteger  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(0x19E3, token0->value);
    TEST_ASSERT_EQUAL_STRING("0x19E3", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token0);
    TEST_ASSERT_EQUAL(1, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token0, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token0, tokenizer->list->tail->data);
  
    token0 = (TokenInteger  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(0x19E3, token0->value);
    TEST_ASSERT_EQUAL_STRING("0x19E3", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
    TokenOperator *token1 = NULL;
    token1 = (TokenOperator *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(OPERATOR_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("/", token1->str);
    TEST_ASSERT_EQUAL(7, token1->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token1);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->tail->data);
  
    token1 = (TokenOperator *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(OPERATOR_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("/", token1->str);
    TEST_ASSERT_EQUAL(7, token1->startColumn);
    freeToken(token1);
  
    TokenFloat  *token2 = NULL;
    token2 = (TokenFloat  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL(FLOAT_TYPE, token2->type);
    TEST_ASSERT_EQUAL(12.e-2, token2->value);
    TEST_ASSERT_EQUAL_STRING("12.e-2", token2->str);
    TEST_ASSERT_EQUAL(8, token2->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token2);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token2, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token2, tokenizer->list->tail->data);
  
    token2 = (TokenFloat  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL(FLOAT_TYPE, token2->type);
    TEST_ASSERT_EQUAL(12.e-2, token2->value);
    TEST_ASSERT_EQUAL_STRING("12.e-2", token2->str);
    TEST_ASSERT_EQUAL(8, token2->startColumn);
    freeToken(token2);
  
    TokenOperator *token3 = NULL;
    token3 = (TokenOperator *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL(OPERATOR_TYPE, token3->type);
    TEST_ASSERT_EQUAL_STRING("*", token3->str);
    TEST_ASSERT_EQUAL(14, token3->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token3);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token3, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token3, tokenizer->list->tail->data);
  
    token3 = (TokenOperator *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL(OPERATOR_TYPE, token3->type);
    TEST_ASSERT_EQUAL_STRING("*", token3->str);
    TEST_ASSERT_EQUAL(14, token3->startColumn);
    freeToken(token3);
  
    TokenIdentifier *token4 = NULL;
    token4 = (TokenIdentifier *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(20, tokenizer->index);
    TEST_ASSERT_EQUAL(IDENTIFIER_TYPE, token4->type);
    TEST_ASSERT_EQUAL_STRING("index", token4->str);
    TEST_ASSERT_EQUAL(15, token4->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token4);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token4, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token4, tokenizer->list->tail->data);
  
    token4 = (TokenIdentifier *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(20, tokenizer->index);
    TEST_ASSERT_EQUAL(IDENTIFIER_TYPE, token4->type);
    TEST_ASSERT_EQUAL_STRING("index", token4->str);
    TEST_ASSERT_EQUAL(15, token4->startColumn);
    freeToken(token4);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpException(ex);
    freeException(ex);
    freeTokenizer(tokenizer);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

