#include "unity.h"
#include "Exception.h"
#include "CException.h"
#include "Tokenizer.h"
#include "Token.h"
#include <malloc.h> 
#include <stdarg.h>
#include  "DoubleLinkedList.h"
#include  "MemAlloc.h"
#include  "TokenizerExceptionThrowing.h"

void setUp(void)
{
}

void tearDown(void)
{
}

CEXCEPTION_T ex;


void  test_createTokenizer_given_number_expect_tokenizer_with_string_19373_created(){
  Tokenizer *tokenizer = createTokenizer("19373");
  TEST_ASSERT_EQUAL_STRING("19373", tokenizer->str);
  TEST_ASSERT_EQUAL(5, tokenizer->length);
  TEST_ASSERT_EQUAL(0, tokenizer->index);
  TEST_ASSERT_EQUAL(0, tokenizer->config);
  TEST_ASSERT_NULL(tokenizer->list);
  freeTokenizer(tokenizer);
}

void  test_createTokenizer_given_identifier_expect_tokenizer_with_string_Hihihi1038w_created(){
  Tokenizer *tokenizer = createTokenizer(" Hihihi1038w");
  TEST_ASSERT_EQUAL_STRING(" Hihihi1038w", tokenizer->str);
  TEST_ASSERT_EQUAL(12, tokenizer->length);
  TEST_ASSERT_EQUAL(0, tokenizer->index);
  TEST_ASSERT_EQUAL(0, tokenizer->config);
  TEST_ASSERT_NULL(tokenizer->list);
  freeTokenizer(tokenizer);
}

void  test_createTokenizer_given_numbers_identifiers_and_operator_expect_tokenizer_with_the_string_created(){
  Tokenizer *tokenizer = createTokenizer("39472 +1972 ajbdd qq");
  TEST_ASSERT_EQUAL_STRING("39472 +1972 ajbdd qq", tokenizer->str);
  TEST_ASSERT_EQUAL(20, tokenizer->length);
  TEST_ASSERT_EQUAL(0, tokenizer->index);
  TEST_ASSERT_EQUAL(0, tokenizer->config);
  TEST_ASSERT_NULL(tokenizer->list);
  freeTokenizer(tokenizer);
}

void  test_configureTokenizer_given_dollar_sign_config_expect_config_1(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" $CCCC");
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  TEST_ASSERT_EQUAL(1, tokenizer->config);
  freeTokenizer(tokenizer);
}

void  test_configureTokenizer_given_hex_dollar_sign_expect_config_3(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  12ADh $1111");
  configureTokenizer(tokenizer, TOKENIZER_HEX_H | TOKENIZER_DOLLAR_SIGN_HEX);
  TEST_ASSERT_EQUAL(3, tokenizer->config);
  freeTokenizer(tokenizer);
}

void  test_configureTokenizer_given_bin_dollar_sign_expect_config_9(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 1234####");
  configureTokenizer(tokenizer, TOKENIZER_BIN_B | TOKENIZER_DOLLAR_SIGN_HEX);
  TEST_ASSERT_EQUAL(9, tokenizer->config);
  freeTokenizer(tokenizer);
}

void  test_configureTokenizer_given_hex_octal_expect_config_6(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("qwerty2345");
  configureTokenizer(tokenizer, TOKENIZER_OCT_O | TOKENIZER_HEX_H);
  TEST_ASSERT_EQUAL(6, tokenizer->config);
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

void  test_skipWhiteSpaces_given_3_spaces_expect_without_space(){
  char  *str = "   qwertyu";
  char  *strWithoutSpace;
  strWithoutSpace = skipWhiteSpaces(str);
  TEST_ASSERT_EQUAL_STRING("qwertyu", strWithoutSpace);
}

void  test_skipWhiteSpaces_given_2_spaces_backslah_t_expect_without_space(){
  char  *str = "  \t4f43u";
  char  *strWithoutSpace;
  strWithoutSpace = skipWhiteSpaces(str);
  TEST_ASSERT_EQUAL_STRING("4f43u", strWithoutSpace);
}

//When encounter \n, it will create newline token so it will no skip \n
void  test_skipWhiteSpaces_given_5spaces_backslash_n_expect_backslash_n_without_space(){
  char  *str = "     \n";
  char  *strWithoutSpace;
  strWithoutSpace = skipWhiteSpaces(str);
  TEST_ASSERT_EQUAL_STRING("\n", strWithoutSpace);
}

void  test_tokenizerSkipSpaces_given_identifier_efnkfsl646_expect_the_same(){
  Tokenizer *tokenizer = createTokenizer("efnkfsl646"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING("efnkfsl646", str);
  TEST_ASSERT_EQUAL(0, tokenizer->index);
  freeTokenizer(tokenizer);
}

void  test_tokenizerSkipSpaces_given____abc123(){
  Tokenizer *tokenizer = createTokenizer("  abc123"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING("abc123", str);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
  freeTokenizer(tokenizer);
}

void  test_tokenizerSkipSpaces_given_backslash_t_expect_backslash_t_skipped(){
  Tokenizer *tokenizer = createTokenizer("\thellllllo"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING("hellllllo", str);
  TEST_ASSERT_EQUAL(1, tokenizer->index);
  freeTokenizer(tokenizer);
}

//When encounter \n, it creates newline token so it does not skip
void  test_tokenizerSkipSpaces_given_backslash_n_expect_backslash_n_skipped(){
  Tokenizer *tokenizer = createTokenizer("\nITEM"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING("\nITEM", str);
  TEST_ASSERT_EQUAL(0, tokenizer->index);
  freeTokenizer(tokenizer);
}

void  test_tokenizerSkipSpaces_given_backslash_v_expect_backslash_v_skipped(){
  Tokenizer *tokenizer = createTokenizer("\v BLOCK"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING("BLOCK", str);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
  freeTokenizer(tokenizer);
}

void  test_tokenizerSkipSpaces_given_backslash_f_expect_backslash_f_skipped(){
  Tokenizer *tokenizer = createTokenizer("\f  GROUP"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL_STRING("GROUP", str);
  TEST_ASSERT_EQUAL(3, tokenizer->index);
  freeTokenizer(tokenizer);
}

void  test_tokenizerSkipSpaces_given____asterisk_expect_empty_spaces_skipped(){
  Tokenizer *tokenizer = createTokenizer("     *"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("*", str);
  freeTokenizer(tokenizer);
}

void  test_tokenizerSkipSpaces_given______0x4573_expect_empty_spaces_skipped(){
  Tokenizer *tokenizer = createTokenizer("     0x4573"); 
  char  *str = tokenizerSkipSpaces(tokenizer);
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("0x4573", str);
  freeTokenizer(tokenizer);
}

void  test_duplicateSubString_given_a_string_and_length_expect_first19_characters_duplicated(){
  char  *str = "DuplicateThisString Hi 193452";
  char  *resultstr;
  resultstr = duplicateSubstring(str, 19);
  TEST_ASSERT_EQUAL_STRING("DuplicateThisString", resultstr);
  free(resultstr);
}

void  test_duplicateSubString_2_given_a_string_and_length_expect_first14_characters_duplicated(){
  char  *str = "This is a test function to test string";
  char  *resultstr;
  resultstr = duplicateSubstring(str, 14);
  TEST_ASSERT_EQUAL_STRING("This is a test", resultstr);
  free(resultstr);
}

void  test_duplicateSubString_2_given_a_number_and_length_expect_first8_characters_duplicated(){
  char  *str = "0x34847ADon't duplicate this!";
  char  *resultstr;
  resultstr = duplicateSubstring(str, 8);
  TEST_ASSERT_EQUAL_STRING("0x34847A", resultstr);
  free(resultstr);
}

void  test_errorIndicator_given_identifier_expect_line_start_at_column_4_with_length_of7_returned(){
  char  *linestr = errorIndicator(4, 7);
  TEST_ASSERT_EQUAL_STRING("    ^~~~~~~", linestr);
  free(linestr);
}

void  test_errorIndicator1_given_identifier_expect_line_start_at_column_6_with_length_of3_returned(){
  char  *linestr = errorIndicator(6, 3);
  TEST_ASSERT_EQUAL_STRING("      ^~~", linestr);
  free(linestr);
}


void  test_getOctalToken_given_035_expect_octal_35(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("035"); 
  IntegerToken *token = NULL;
  Try{
    token = getOctalToken(tokenizer);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("035", token->str);
    TEST_ASSERT_EQUAL(035, token->value);
    TEST_ASSERT_EQUAL(3, token->length);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getOctalToken_given_063_expect_octal_63(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  063"); 
  IntegerToken *token = NULL;
  Try{
    token = getOctalToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("063", token->str);
    TEST_ASSERT_EQUAL(063, token->value);
    TEST_ASSERT_EQUAL(3, token->length);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getOctalToken_given_0101_string_expect_octal_101(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   0101\"  \""); 
  IntegerToken *token = NULL;
  Try{
    token = getOctalToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(0101, token->value);
    TEST_ASSERT_EQUAL_STRING("0101", token->str);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getOctalToken_given_0765_backslash_t_expect_octal_765(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0765\t"); 
  IntegerToken *token = NULL;
  Try{
    token = getOctalToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(0765, token->value);
    TEST_ASSERT_EQUAL_STRING("0765", token->str);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getOctalToken_given_0264_backslash_n_expect_octal_264(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0264\n#"); 
  IntegerToken *token = NULL;
  Try{
    token = getOctalToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(0264, token->value);
    TEST_ASSERT_EQUAL_STRING("0264", token->str);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getOctalToken_given_01239_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("01239"); 
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_0123_11_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  0123_11"); 
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_0o35_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0o35"); 
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_0oa5_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0oa5"); 
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_0a5_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0a5"); 
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_085_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("085"); 
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_451o_without_oct_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 451o (No oct config)"); 
  IntegerToken *token = NULL;
  Try{
    token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_451o_with_oct_config_expect_octal_63(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 451o"); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  IntegerToken *token = NULL;
  Try{
    token = getOctalToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(0451, token->value);
    TEST_ASSERT_EQUAL_STRING("451o", token->str);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getOctalToken_given_13O_backslash_t_with_oct_config_expect_octal_13(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   13O\t"); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  IntegerToken *token = NULL;
  Try{
    token = getOctalToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(013, token->value);
    TEST_ASSERT_EQUAL_STRING("13O", token->str);
    TEST_ASSERT_EQUAL(3, token->length);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getOctalToken_given_777o__with_oct_config_expect_octal_777(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 777o _"); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  IntegerToken *token = NULL;
  Try{
    token = getOctalToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(0777, token->value);
    TEST_ASSERT_EQUAL_STRING("777o", token->str);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getOctalToken_given_85of_with_oct_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  85of "); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_085o_with_oct_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  085o "); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_043point52_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  043.52 "); 
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_034__expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 034_ "); 
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_01110b_no_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 01110b (no bin config)"); 
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}


// There are possibilities where binary value start with 0
void  test_getOctalToken_given_01110b_with_bin_config_expect_bin_1110(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  01110b  "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
    token = getOctalToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(0b1110, token->value);
    TEST_ASSERT_EQUAL_STRING("01110b", token->str);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getOctalToken_given_01000b__with_bin_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  01000b_"); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_01110b_point123_with_bin_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  01110b.123"); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

//There are possibilities where hexadecimal number start with 0
void  test_getOctalToken_given_0A35h_with_hex_config_expect_hex_0x0A35(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  0A35h  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = getOctalToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(0x0A35, token->value);
    TEST_ASSERT_EQUAL_STRING("0A35h", token->str);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getOctalToken_given_0983h_with_hex_config_expect_hex_0x0983(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   0983h "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = getOctalToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(0x0983, token->value);
    TEST_ASSERT_EQUAL_STRING("0983h", token->str);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getOctalToken_given_0AA3EH__with_hex_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0AA3EH_   "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_00F3CCH4533_with_hex_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0F3CCH4533   "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_0ABCD_with_hex_config_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   0ABCD  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
  token = getOctalToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOctalToken_given_01101bh_with_hex_and_bin_config_expect_hex_0x01101b(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  01101bh  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H | TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
    token = getOctalToken(tokenizer);
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    TEST_ASSERT_EQUAL(0x01101b, token->value);
    TEST_ASSERT_EQUAL_STRING("01101bh", token->str);
    TEST_ASSERT_EQUAL(7, token->length);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getHexToken_given_0x55_expect_hex_0x55(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0x55"); 
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL(0x55, token->value);
    TEST_ASSERT_EQUAL_STRING("0x55", token->str);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getHexToken_given_0X93A2_expect_hex_0x93A2(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  0X93A2  "); 
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(0X93A2, token->value);
    TEST_ASSERT_EQUAL_STRING("0X93A2", token->str);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getHexToken_given_0x999_and_Symbol_expect_0x999(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("     0x999&"); 
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
    TEST_ASSERT_EQUAL(10, tokenizer->index);
    TEST_ASSERT_EQUAL(0x999, token->value);
    TEST_ASSERT_EQUAL_STRING("0x999", token->str);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(5, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getHexToken_given_0x7ADC_backslash_n_expect_0x7ADC(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  0x7ADC\n"); 
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(0x7ADC, token->value);
    TEST_ASSERT_EQUAL_STRING("0x7ADC", token->str);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getHexToken_given_0xx5_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0xx5"); 
  IntegerToken *token = NULL;
  Try{
  token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);  
  }
  freeTokenizer(tokenizer);
}

void  test_getHexToken_given_0x456__expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0x456_"); 
  IntegerToken *token = NULL;
  Try{
  token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
  }
  freeTokenizer(tokenizer);
}


void  test_getHexToken_given_00x76_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("00x76"); 
  IntegerToken *token = NULL;
  Try{
  token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
  }
  freeTokenizer(tokenizer);
}


void  test_getHexToken_given_0xface_expect_hex_0xface(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0xface"); 
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(0xface, token->value);
    TEST_ASSERT_EQUAL_STRING("0xface", token->str);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getHexToken_given_0xAG23_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("00xAG23"); 
  IntegerToken *token = NULL;
  Try{
  token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);  
  }
  freeTokenizer(tokenizer);
}

void  test_getHexToken_39Ah_without_hex_config_expect_ERROR_INVALID_INTEGER_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   39Ah (No hex config) "); 
  IntegerToken *token = NULL;
  Try{
  token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
  }
  freeTokenizer(tokenizer);
}

void  test_getHexToken_given_39Ah_with_hex_config_expect_0x39A(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   39Ah  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(0x39A, token->value);
    TEST_ASSERT_EQUAL_STRING("39Ah", token->str);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getHexToken_given_1928H_backslash_t_with_hex_config_expect_0x1928(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  1928H\t  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(0x1928, token->value);
    TEST_ASSERT_EQUAL_STRING("1928H", token->str);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getHexToken_given_31DEh_t_with_hex_config_expect_0x31DE(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  31DEh  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(0x31DE, token->value);
    TEST_ASSERT_EQUAL_STRING("31DEh", token->str);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getHexToken_given_82ACH12_with_hex_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   82ACH12  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
  token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);  
  }
  freeTokenizer(tokenizer);
}

void  test_getHexToken_given_0xC34Ah_with_hex_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   0xC34Ah  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
  token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
  }
  freeTokenizer(tokenizer);
}

void  test_getHexToken_given_dollarSign_FADA_with_dollarSign_config_expect_hexadecimal_0xFADA(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   $FADA "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL_STRING("$FADA", token->str);
    TEST_ASSERT_EQUAL(0xFADA, token->value);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getHexToken_given_dollarSign_02AF1_with_dollarSign_config_expect_hexadecimal_0x02AF1(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   $02AF1 "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL_STRING("$02AF1", token->str);
    TEST_ASSERT_EQUAL(0x02AF1, token->value);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getHexToken_given_dollarSign_FADA_with_dollarSign_config_expect_hexadecimal_0x88A1(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   $88A1 hellllo "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL_STRING("$88A1", token->str);
    TEST_ASSERT_EQUAL(0x88A1, token->value);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getHexToken_given_dollarSign_FADAh_with_dollarSign_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   $34A1h "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX | TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode); 
  }
  freeTokenizer(tokenizer);
}

void  test_getHexToken_given_dollarSign_39W1_with_dollarSign_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   $39W1 "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode); 
  }
  freeTokenizer(tokenizer);
}

void  test_getHexToken_given_dollarSign_12A3Y__with_dollarSign_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   $12A3Y "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode); 
  }
  freeTokenizer(tokenizer);
}

void  test_getHexToken_given_dollarSign_0x3451_with_dollarSign_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   0x3451h "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
  }
  freeTokenizer(tokenizer);
}

void  test_getHexToken_given_0x3391point88_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   0x3391.88 "); 
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
  }
  freeTokenizer(tokenizer);
}

void  test_getHexToken_given_dollarSign_abc_point_21_with_sign_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  $abc.21 "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;
  Try{
    token = getHexToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_1point456_expect_floating_point_1point456(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1.456"); 
  FloatToken *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(1.456, token->value);
    TEST_ASSERT_EQUAL_STRING("1.456", token->str);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_256point_expect_floating_point_256point(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  256."); 
  FloatToken *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(256., token->value);
    TEST_ASSERT_EQUAL_STRING("256.", token->str);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_66point191_or_symbol_expect_66point191(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("       66.191^"); 
  FloatToken *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(13, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(66.191, token->value);
    TEST_ASSERT_EQUAL_STRING("66.191", token->str);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(7, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_74point_e_expect_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  74.e  3567"); /////////////////
  FloatToken *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);  
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_101point191halo_expect_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 101.191halo");
  FloatToken *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_1apoint456_expect_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1a.456"); 
  FloatToken *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode); 
  }
  freeTokenizer(tokenizer);
}


void  test_getFloatToken_given_3pointpoint847_expect_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("3..847"); 
  FloatToken *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);  
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_4point1111__expect_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  4.1111_"); 
  FloatToken *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_3point836e2_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("3.836e2"); 
  FloatToken *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(3.836e2, token->value);
    TEST_ASSERT_EQUAL_STRING("3.836e2", token->str);
    TEST_ASSERT_EQUAL(7, token->length);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_7pointe2_expect_7point_e2(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  7.e2"); 
  FloatToken *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(7.e2, token->value);
    TEST_ASSERT_EQUAL_STRING("7.e2", token->str);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_e2_expect_0point_e2(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0.e2"); 
  FloatToken *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(0.e2, token->value);
    TEST_ASSERT_EQUAL_STRING("0.e2", token->str);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}
  
void  test_getFloatToken_given_53point12eplus2_expect_53point12eplus2(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("53.12e+2"); 
  FloatToken *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(53.12e+2, token->value);
    TEST_ASSERT_EQUAL_STRING("53.12e+2", token->str);
    TEST_ASSERT_EQUAL(8, token->length);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_18356point123eminus4_expect_18356point123eminus4(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("18356.123e-4"); 
  FloatToken *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(18356.123e-4, token->value);
    TEST_ASSERT_EQUAL_STRING("18356.123e-4", token->str);
    TEST_ASSERT_EQUAL(12, token->length);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_186point13minus4_expect_186point13minus4(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("186.13-4"); 
  FloatToken *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(186.13, token->value);
    TEST_ASSERT_EQUAL_STRING("186.13", token->str);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_384e_minus2_backslash_n_expect_384e_minus2(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  384e-2\n"); 
  FloatToken *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(384e-2, token->value);
    TEST_ASSERT_EQUAL_STRING("384e-2", token->str);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_1point034eplus3plus12_expect_1point034eplus3(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1.034e+3+12"); 
  FloatToken *token = NULL;
  Try{
    token = getFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(1.034e+3, token->value);
    TEST_ASSERT_EQUAL_STRING("1.034e+3", token->str);
    TEST_ASSERT_EQUAL(8, token->length);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getFloatToken_given_154xpoint395_expect_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("154x.395"); 
  FloatToken *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_654e_minus2_abc_expect_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   654e-2_abc /3  "); 
  FloatToken *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_19epoint5_expect_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("19e.5"); 
  FloatToken *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);  
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_12point4point4point2point_e_minus_minus_4_expect_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("     12.4.4.2.e--4         "); 
  FloatToken *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_397point2y0_expect_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("397.2y0"); 
  FloatToken *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);  
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_1point456eplus_plus3_expect_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1.456e++3"); 
  FloatToken *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode); 
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_1point456eminus_minus3_expect_ERROR_INVALID_FLOAT_exception_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1.456e--3"); 
  FloatToken *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_1point456emultiply8_expect_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1.456e*8"); 
  FloatToken *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);   
  }
  freeTokenizer(tokenizer);
}

void  test_getFloatToken_given_12point1eslash5_expect_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("12.1e/5"); 
  FloatToken *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);    
  }
  freeTokenizer(tokenizer);
}


void  test_getFloatToken_given_81point3eplusq_expect_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  81.3e+q  "); 
  FloatToken *token = NULL;
  Try{
  token = getFloatToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);   
  }
  freeTokenizer(tokenizer);
}

void  test_getBinToken_given_0b110_expect_decimal_6(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b110"); 
  IntegerToken *token = NULL;
  Try{
    token = getBinToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(6, token->value);
    TEST_ASSERT_EQUAL_STRING("0b110", token->str);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getBinToken_given_0B111_expect_decimal_7(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  0B111  "); 
  IntegerToken *token = NULL;
  Try{
    token = getBinToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(7, token->value);
    TEST_ASSERT_EQUAL_STRING("0B111", token->str);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getBinToken_given_0B10111backslash_n_expect_0B10111(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0B10111\n  "); 
  IntegerToken *token = NULL;
  Try{
    token = getBinToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(0B10111, token->value);
    TEST_ASSERT_EQUAL_STRING("0B10111", token->str);
    TEST_ASSERT_EQUAL(7, token->length);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getBinToken_given_0b1111_expect_decimal_15(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b1111"); 
  IntegerToken *token = NULL;
  Try{
    token = getBinToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(15, token->value);
    TEST_ASSERT_EQUAL_STRING("0b1111", token->str);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getBinToken_given_0b1011010remainder_expect_decimal_90(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("      0b1011010%"); 
  IntegerToken  *token = NULL;
  Try{
    token = getBinToken(tokenizer);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(90, token->value);
    TEST_ASSERT_EQUAL_STRING("0b1011010", token->str);
    TEST_ASSERT_EQUAL(9, token->length);
    TEST_ASSERT_EQUAL(6, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getBinToken_given_0b1131_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b1131"); 
  IntegerToken *token = NULL;
  Try{
  token = getBinToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);  
  }
  freeTokenizer(tokenizer);
}

void  test_getBinToken_given_0b11P0_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  0b11P0  "); 
  IntegerToken *token = NULL;
  Try{
  token = getBinToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getBinToken_given_0b1100point123_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  0b1100.123  "); 
  IntegerToken *token = NULL;
  Try{
  token = getBinToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getBinToken_given_0b10010plusplus_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    0b10010plusplus  "); 
  IntegerToken *token = NULL;
  Try{
  token = getBinToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getBinToken_given_10101b_without_bin_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    10101b  (No config) "); 
  IntegerToken *token = NULL;
  Try{
  token = getBinToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getBinToken_given_10101b_with_bin_config_expect_decimal_21(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 10101b"); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
    token = getBinToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(0b10101, token->value);
    TEST_ASSERT_EQUAL_STRING("10101b", token->str);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getBinToken_given_10110b__hi_with_bin_config_expect_decimal_22(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 10110b hi"); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
    token = getBinToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(0b10110, token->value);
    TEST_ASSERT_EQUAL_STRING("10110b", token->str);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getBinToken_given_10111b_backslash_n_with_bin_config_expect_decimal_23(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 10111b\n  "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
    token = getBinToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL_FLOAT(0b10111, token->value);
    TEST_ASSERT_EQUAL_STRING("10111b", token->str);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getBinToken_given_1101bP_with_bin_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    1101bP  "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
  token = getBinToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getBinToken_given_1021b_with_bin_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    1021b  "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
  token = getBinToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getBinToken_given_0b0011b_with_bin_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    0b0011b  "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
  token = getBinToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getBinToken_given_10101bpoint234_with_bin_config_expect_exception_ERROR_INVALID_INTEGER_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    10101b.234 "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
  token = getBinToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_351_expect_351(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("351"); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(3, token->length);
    TEST_ASSERT_EQUAL(351, token->value);
    TEST_ASSERT_EQUAL_STRING("351", token->str);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_87bracket_expect_decimal_87(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  87("); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(2, token->length);
    TEST_ASSERT_EQUAL(87, token->value);
    TEST_ASSERT_EQUAL_STRING("87", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_1a35_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("1a35"); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_78wxy_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  78wxy@"); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_873Ah_without_hex_config_expect_exception_ERROR_INVALID_INTEGER_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  873Ah  (No HEX config)"); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_873Ah_with_hex_config_expect_hexadecimal_0x873A(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  873Ah  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(0x873A, token->value);
    TEST_ASSERT_EQUAL_STRING("873Ah", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_D43Ah_plus_with_hex_config_expect_hexadecimal_0xD43A(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   D43Ah+  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(0xD43A, token->value);
    TEST_ASSERT_EQUAL_STRING("D43Ah", token->str);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_ABCDH_with_hex_config_expect_hexadecimal_34723(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    ABCDH  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H | TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(0xABCD, token->value);
    TEST_ASSERT_EQUAL_STRING("ABCDH", token->str);
    TEST_ASSERT_EQUAL(4, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_34A2h_Q_with_hex_config_expect_hexadecimal_0x34A2(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  34A2h Q "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H | TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(0x34A2, token->value);
    TEST_ASSERT_EQUAL_STRING("34A2h", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_52__with_hex_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  10E3h_ "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_10E3h653__with_hex_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  10E3h653"); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_5R34h_with_hex_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  5R34h"); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_FDECHell__with_hex_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" FDECHell"); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}


void  test_getDecimalOrFloatToken_given_10001b_without_bin_config_expect_exception_ERROR_INVALID_INTEGER_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   10001b (without bin config) "); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_10110b_with_bin_config_expect_bin_10110(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    10110b  "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(10, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(0b10110, token->value);
    TEST_ASSERT_EQUAL_STRING("10110b", token->str);
    TEST_ASSERT_EQUAL(4, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_101B_with_bin_config_expect_bin_101(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  101B  "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(0b101, token->value);
    TEST_ASSERT_EQUAL_STRING("101B", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_10101b_minus_with_bin_config_expect_bin_10101(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  10101b-  "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(6, token->length);
    TEST_ASSERT_EQUAL(0b10101, token->value);
    TEST_ASSERT_EQUAL_STRING("10101b", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_10101b__with_bin_config_expect_bin_1100(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  1100b _  "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(0B1100, token->value);
    TEST_ASSERT_EQUAL_STRING("1100b", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_10111b_hello__with_bin_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 10111b_hello"); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_11201b_with_bin_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 11201b   "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_11111b43_hello__with_bin_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  11111b43"); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_134o_without_oct_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  134o (without oct config)"); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_134o_with_oct_config_expect_oct_134(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   134o "); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(0134, token->value);
    TEST_ASSERT_EQUAL_STRING("134o", token->str);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_0111o_with_oct_config_expect_oct_111(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   0111o "); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(5, token->length);
    TEST_ASSERT_EQUAL(0111, token->value);
    TEST_ASSERT_EQUAL_STRING("0111o", token->str);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_413O_backslash_t_with_oct_config_expect_oct_413(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   413O\t "); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(0413, token->value);
    TEST_ASSERT_EQUAL_STRING("413O", token->str);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_173O_ab_with_oct_config_expect_oct_0173(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  173O ab "); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL(0173, token->value);
    TEST_ASSERT_EQUAL_STRING("173O", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_3945o_with_oct_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  3945o "); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_12o_hello_with_oct_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  12o_hello "); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_148o_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    148o  (no oct config) "); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_354point331_expect_getFloatToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 354.331/#@$ "); 
  FloatToken *token = NULL;
  Try{
    token = (FloatToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL(7, token->length);
    TEST_ASSERT_EQUAL(354.331, token->value);
    TEST_ASSERT_EQUAL_STRING("354.331", token->str);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_20203e_minus_3_expect_getFloatToken_called(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   20203e-3*1010101 "); 
  FloatToken *token = NULL;
  Try{
    token = (FloatToken *)getDecimalOrFloatToken(tokenizer);
    TEST_ASSERT_EQUAL(11, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL(8, token->length);
    TEST_ASSERT_EQUAL(20203e-3, token->value);
    TEST_ASSERT_EQUAL_STRING("20203e-3", token->str);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getDecimalOrFloatToken_given_876hpoint1020_with_hex_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  876h.1020 "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  FloatToken *token = NULL;
  Try{
    token = (FloatToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_1001b_point88_with_bin_config_expect_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  1001b.88 "); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  FloatToken *token = NULL;
  Try{
    token = (FloatToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_674point7y49_expect_exception_to_be_thrown_invalid_float(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  674.7y49 "); 
  FloatToken *token = NULL;
  Try{
    token = (FloatToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getDecimalOrFloatToken_given_9e_minus_e2_expect_exception_to_be_thrown_invalid_float(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 9e-e2 "); 
  FloatToken *token = NULL;
  Try{
    token = (FloatToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given____hihihi123_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("___hihihi123"); 
  IdentifierToken *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(12, tokenizer->index);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL_STRING("___hihihi123", token->str);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  TEST_ASSERT_EQUAL(12, token->length);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given_totalIsplus123_expect_totalIs(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("totalIs+123"); 
  IdentifierToken *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(7, tokenizer->index);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL_STRING("totalIs", token->str);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  TEST_ASSERT_EQUAL(7, token->length);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given_calculate_this01c_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  calculate_this01c "); 
  IdentifierToken *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(19, tokenizer->index);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL_STRING("calculate_this01c", token->str);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  TEST_ASSERT_EQUAL(17, token->length);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given_spacex3acerE15_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   acerE15 "); 
  IdentifierToken *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(10, tokenizer->index);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL_STRING("acerE15", token->str);
  TEST_ASSERT_EQUAL(3, token->startColumn);
  TEST_ASSERT_EQUAL(7, token->length);
  freeToken(token);
  freeTokenizer(tokenizer);
}


void  test_getIdentifierToken_given_hello_123_expect_hello(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("hello 123"); 
  IdentifierToken *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL_STRING("hello", token->str);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  TEST_ASSERT_EQUAL(5, token->length);
  freeToken(token);
  freeTokenizer(tokenizer);
}
  
void  test_getIdentifierToken_given_movwf123plus_expect_movwf(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("movwf123+"); 
  IdentifierToken *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(8, tokenizer->index);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL_STRING("movwf123", token->str);
  TEST_ASSERT_EQUAL(0, token->startColumn);
  TEST_ASSERT_EQUAL(8, token->length);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given_Iden913__minus0x13_expect__Iden913__(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  _Iden913__-0x13 "); 
  IdentifierToken *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(12, tokenizer->index);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL_STRING("_Iden913__", token->str);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  TEST_ASSERT_EQUAL(10, token->length);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given_rw239dmw_backslash_n_expect_without_backslash_n(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   rw239dmw\n "); 
  IdentifierToken *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(11, tokenizer->index);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL_STRING("rw239dmw", token->str);
  TEST_ASSERT_EQUAL(3, token->startColumn);
  TEST_ASSERT_EQUAL(8, token->length);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given_addwf_StringHere_expect_without_String(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   addwf\"A string xx\""); 
  IdentifierToken *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(8, tokenizer->index);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL_STRING("addwf", token->str);
  TEST_ASSERT_EQUAL(3, token->startColumn);
  TEST_ASSERT_EQUAL(5, token->length);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given_DE2AH_no_config_expect_identifier_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   DE2AH  (No hex config)"); 
  IdentifierToken *token = NULL;
  token = getIdentifierToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL(8, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("DE2AH", token->str);
  TEST_ASSERT_EQUAL(3, token->startColumn);
  TEST_ASSERT_EQUAL(5, token->length);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getIdentifierToken_given_DE2AH_with_hex_config_expect_integer_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   DE2AH  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getIdentifierToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(0xDE2A, token->value);
    TEST_ASSERT_EQUAL_STRING("DE2AH", token->str);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    TEST_ASSERT_EQUAL(5, token->length);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getIdentifierToken_given_ADE333_with_hex_config_expect_identifier_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  ADE333  "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IdentifierToken *token = NULL;
  Try{
    token = (IdentifierToken *)getIdentifierToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("ADE333", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    TEST_ASSERT_EQUAL(6, token->length);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getIdentifierToken_given_identifier_identifier_integer_identifier_with_hex_config_expect_identifier__identifier_integer_integer_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  hell qwert abcdh _123h "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken *)getIdentifierToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("hell", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    TEST_ASSERT_EQUAL(4, token0->length);
    freeToken(token0);
    
    IdentifierToken *token1 = NULL;
    token1 = (IdentifierToken *)getIdentifierToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token1->type);
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("qwert", token1->str);
    TEST_ASSERT_EQUAL(7, token1->startColumn);
    TEST_ASSERT_EQUAL(5, token1->length);
    freeToken(token1);
    
    IntegerToken  *token2 = NULL;
    token2 = (IntegerToken  *)getIdentifierToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token2->type);
    TEST_ASSERT_EQUAL(18, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("abcdh", token2->str);
    TEST_ASSERT_EQUAL(0xABCD, token2->value);
    TEST_ASSERT_EQUAL(13, token2->startColumn);
    TEST_ASSERT_EQUAL(5, token2->length);
    freeToken(token2);
    
    IdentifierToken *token3 = NULL;
    token3 = (IdentifierToken *)getIdentifierToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token3->type);
    TEST_ASSERT_EQUAL(24, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("_123h", token3->str);
    TEST_ASSERT_EQUAL(19, token3->startColumn);
    TEST_ASSERT_EQUAL(5, token3->length);
    freeToken(token3);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getIdentifierToken_given_FA12h_symbol_with_hex_config_expect_identifier_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  FA12h> "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getIdentifierToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("FA12h", token->str);
    TEST_ASSERT_EQUAL(0xFA12, token->value);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    TEST_ASSERT_EQUAL(5, token->length);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getIdentifierToken_given_F12Ah_point123_with_hex_config_expect_getHexToken_called_exception_ERROR_INVALID_INTEGER_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  F12Ah.123   "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getIdentifierToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

//This is taken as identifier, not hexadecimal since underscore after h
void  test_getIdentifierToken_given_A12Eh_123_with_hex_config_expect_identifier_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  A12Eh_123 "); 
  configureTokenizer(tokenizer, TOKENIZER_HEX_H);
  IdentifierToken *token = NULL;
  Try{
    token = getIdentifierToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
    TEST_ASSERT_EQUAL(11, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("A12Eh_123", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    TEST_ASSERT_EQUAL(9, token->length);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getNumberToken_given_375_expect_getDecimalOrFloatToken_called_decimal_375(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("375"); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL(375, token->value);
    TEST_ASSERT_EQUAL_STRING("375", token->str);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}


void  test_getNumberToken_given_87point9234_expect_getFloatToken_called_87point9234(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("87.9234"); 
  FloatToken *token = NULL;
  Try{
    token = (FloatToken *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(87.9234, token->value);
    TEST_ASSERT_EQUAL_STRING("87.9234", token->str);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getNumberToken_given_0point222e_plus2_expect_getFloatToken_called_87point9234(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  0.222e+2   "); 
  FloatToken *token = NULL;
  Try{
    token = (FloatToken *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL(10, tokenizer->index);
    TEST_ASSERT_EQUAL(0.222e+2, token->value);
    TEST_ASSERT_EQUAL_STRING("0.222e+2", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getNumberToken_given_93point_e_minus2_expect_getFloatToken_called_93point_e_minus2(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   93.e-2  "); 
  FloatToken *token = NULL;
  Try{
    token = (FloatToken *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL(93.e-2, token->value);
    TEST_ASSERT_EQUAL_STRING("93.e-2", token->str);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getNumberToken_given_0x9521_expect_getHexToken_called_hex_0x9521(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0x9521"); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(0x9521, token->value);
    TEST_ASSERT_EQUAL_STRING("0x9521", token->str);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getNumberToken_given_0b1010_expect_getBinToken_called_bin_0b1010(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b1010"); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(0b1010, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getNumberToken_given_0345_expect_getOctToken_called_oct_0345(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0345"); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(0345, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getNumberToken_given_0139_expect_getOctalToken_called_exception_ERROR_INVALID_INTEGER_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    0139"); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getNumberToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_0553point532_expect_getOctalToken_called_exception_ERROR_INVALID_INTEGER_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    0553.532"); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getNumberToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_32point12point3_expect_getFloatToken_called_exception_ERROR_INVALID_FLOAT_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("32.12.3"); 
  FloatToken *token = NULL;
  Try{
  token = (FloatToken *)getNumberToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_34point_e_excalmation_1_expect_getFloatToken_called_exception_ERROR_INVALID_FLOAT_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  34.e!1 "); 
  FloatToken *token = NULL;
  Try{
  token = (FloatToken *)getNumberToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_54b_expect_getIntegerToken_called_exception_ERROR_INVALID_INTEGER_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  54b"); 
  IntegerToken *token = NULL;
  Try{
  token = (IntegerToken *)getNumberToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_0b1211_expect_getBinToken_called_exception_ERROR_INVALID_INTEGER_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b1211"); 
  IntegerToken *token = NULL;
  Try{
  token = (IntegerToken *)getNumberToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_0x3Y12_expect_getHexToken_called_exception_ERROR_INVALID_INTEGER_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0x3Y12"); 
  IntegerToken *token = NULL;
  Try{
  token = (IntegerToken *)getNumberToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_0o318_expect_getOctToken_called_exception_ERROR_INVALID_INTEGER_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0o318"); 
  IntegerToken *token = NULL;
  Try{
  token = (IntegerToken *)getNumberToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_0345_12point3e2_12_0x123_backslash_n_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0345 12.3e2 12 0x123\n"); 
  IntegerToken *token0 = NULL;
  Try{
    token0 = (IntegerToken *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(0345, token0->value);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
    FloatToken  *token1 = NULL;
    token1 = (FloatToken  *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token1->type);
    TEST_ASSERT_EQUAL_FLOAT(12.3e2, token1->value);
    TEST_ASSERT_EQUAL(6, token1->startColumn);
    freeToken(token1);
  
    IntegerToken *token2 = NULL;
    token2 = (IntegerToken *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token2->type);
    TEST_ASSERT_EQUAL(12, token2->value);
    TEST_ASSERT_EQUAL(13, token2->startColumn);
    freeToken(token2);
  
    IntegerToken *token3 = NULL;
    token3 = (IntegerToken *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(21, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token3->type);
    TEST_ASSERT_EQUAL(0x123, token3->value);
    TEST_ASSERT_EQUAL(16, token3->startColumn);
    freeToken(token3);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void  test_getNumberToken_given_0x123_456_32point_e_plus_minus_2_expect_getOctToken_called_exception_ERROR_INVALID_FLOAT_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0x123 456 32.e+-2 0b1010"); 
  IntegerToken *token0 = NULL;
  Try{
  token0 = (IntegerToken *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
  TEST_ASSERT_EQUAL(0x123, token0->value);
  TEST_ASSERT_EQUAL(1, token0->startColumn);
  freeToken(token0);
  
  IntegerToken *token1 = NULL;
  token1 = (IntegerToken *)getNumberToken(tokenizer);
  TEST_ASSERT_EQUAL(10, tokenizer->index);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token1->type);
  TEST_ASSERT_EQUAL(456, token1->value);
  TEST_ASSERT_EQUAL(7, token1->startColumn);
  freeToken(token1);
  
  FloatToken *token2 = NULL;
  token2 = (FloatToken *)getNumberToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getNumberToken_given_19A9H_177o_101111b_3_configs_expect_0x19A9_0177_0b101111(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  19A9H 177o   101111b"); 
  configureTokenizer(tokenizer, TOKENIZER_BIN_B | TOKENIZER_HEX_H | TOKENIZER_OCT_O);
  IntegerToken *token0 = NULL;
  Try{
    token0 = (IntegerToken *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(0x19A9, token0->value);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
    
    IntegerToken  *token1 = NULL;
    token1 = (IntegerToken  *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token1->type);
    TEST_ASSERT_EQUAL(0177, token1->value);
    TEST_ASSERT_EQUAL(8, token1->startColumn);
    freeToken(token1);
    
    IntegerToken  *token2 = NULL;
    token2 = (IntegerToken  *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(22, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token2->type);
    TEST_ASSERT_EQUAL(0b101111, token2->value);
    TEST_ASSERT_EQUAL(15, token2->startColumn);
    freeToken(token2);    
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getNumberToken_given_0F123H_09123h_with_oct_hex_config_expect_integer_0xF123_0x9123_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   0F123H  09123h 01100bH"); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O | TOKENIZER_HEX_H);
  IntegerToken *token0 = NULL;
  Try{
    token0 = (IntegerToken  *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    TEST_ASSERT_EQUAL(0xF123, token0->value);
    TEST_ASSERT_EQUAL_STRING("0F123H", token0->str);
    TEST_ASSERT_EQUAL(3, token0->startColumn);
    freeToken(token0);
    
    IntegerToken  *token1 = NULL;
    token1 = (IntegerToken  *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token1->type);
    TEST_ASSERT_EQUAL(17, tokenizer->index);
    TEST_ASSERT_EQUAL(0x9123, token1->value);
    TEST_ASSERT_EQUAL_STRING("09123h", token1->str);
    TEST_ASSERT_EQUAL(11, token1->startColumn);
    freeToken(token1);
    
    IntegerToken  *token2 = NULL;
    token2 = (IntegerToken  *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token2->type);
    TEST_ASSERT_EQUAL(25, tokenizer->index);
    TEST_ASSERT_EQUAL(0x1100B, token2->value);
    TEST_ASSERT_EQUAL_STRING("01100bH", token2->str);
    TEST_ASSERT_EQUAL(18, token2->startColumn);
    freeToken(token2);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");   
  }
}

void  test_getNumberToken_given_01100b_with_bin_config_expect_integer_0b1100_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  01100b "); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O | TOKENIZER_HEX_H | TOKENIZER_BIN_B);
  IntegerToken *token0 = NULL;
  Try{
    token0 = (IntegerToken  *)getNumberToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(0b1100, token0->value);
    TEST_ASSERT_EQUAL_STRING("01100b", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");   
  }
}

void  test_getOperatorToken_given_minus_expect_minus(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  - "); 
  OperatorToken *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(3, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("-", token->str);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_multiply_expect_multiply(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    * "); 
  OperatorToken *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("*", token->str);
  TEST_ASSERT_EQUAL(4, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_divide_expect_divide(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" / "); 
  OperatorToken *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("/", token->str);
  TEST_ASSERT_EQUAL(1, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_remainder_expect_remainder(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" % "); 
  OperatorToken *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("%", token->str);
  TEST_ASSERT_EQUAL(1, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_AND_expect_AND(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("     &  "); 
  OperatorToken *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("&", token->str);
  TEST_ASSERT_EQUAL(5, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_OR_expect_OR(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   |  "); 
  OperatorToken *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(4, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("|", token->str);
  TEST_ASSERT_EQUAL(3, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_parentheses_expect_parentheses(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("     (  "); 
  OperatorToken *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("(", token->str);
  TEST_ASSERT_EQUAL(5, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_braces_expect_braces(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  {  "); 
  OperatorToken *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(3, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("{", token->str);
  TEST_ASSERT_EQUAL(2, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_square_bracket_expect_bracket(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" [  "); 
  OperatorToken *token = NULL;
  token = getOperatorToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
  TEST_ASSERT_EQUAL_STRING("[", token->str);
  TEST_ASSERT_EQUAL(1, token->startColumn);
  freeToken(token);
  freeTokenizer(tokenizer);
} 

void  test_getOperatorToken_given_dollar_sign_hex_value_no_config_expect_hex_token_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" $19A3  (No $ config)"); 
  OperatorToken *token = NULL;  
  Try{
    token = getOperatorToken(tokenizer);
    TEST_ASSERT_EQUAL(2, tokenizer->index);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    TEST_ASSERT_EQUAL_STRING("$", token->str);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getOperatorToken_given_dollar_sign_space_hex_value_with_config_expect_operator_token_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" $  19A3  "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  OperatorToken *token = NULL;  
  Try{
    token = getOperatorToken(tokenizer);
    TEST_ASSERT_EQUAL(2, tokenizer->index);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    TEST_ASSERT_EQUAL_STRING("$", token->str);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getOperatorToken_given_dollar_sign__FADE12h_with_config_expect_operator_token_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" $_FADE12h  "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  OperatorToken *token = NULL;  
  Try{
    token = getOperatorToken(tokenizer);
    TEST_ASSERT_EQUAL(2, tokenizer->index);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    TEST_ASSERT_EQUAL_STRING("$", token->str);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getOperatorToken_given_dollar_sign_hex_value_with_sign_config_expect_hex_token_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" $19A3 hello  "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;  
  Try{
    token = (IntegerToken *)getOperatorToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(0x19A3, token->value);
    TEST_ASSERT_EQUAL_STRING("$19A3", token->str);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getOperatorToken_given_dollar_sign_39AF_backslash_n_with_sign_config_expect_hex_token_0x39AF_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" $39AF\n "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;  
  Try{
    token = (IntegerToken *)getOperatorToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(0x39AF, token->value);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getOperatorToken_given_dollar_sign_91AAabcdefg_with_sign_config_expect_exception_ERROR_INVALID_INTEGER_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   $91AAabcdefg  "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;  
  Try{
    token = (IntegerToken *)getOperatorToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
      dumpTokenErrorMessage(ex, 1);
      TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
      freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOperatorToken_given_dollar_sign_76T5_with_sign_config_expect_exception_ERROR_INVALID_INTEGER_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   $76T5  "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;  
  Try{
    token = (IntegerToken *)getOperatorToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
      dumpTokenErrorMessage(ex, 1);
      TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
      freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOperatorToken_given_dollar_sign_0x88A8_with_sign_config_expect_exception_ERROR_INVALID_INTEGER_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   $0x88A8  "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;  
  Try{
    token = (IntegerToken *)getOperatorToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
      dumpTokenErrorMessage(ex, 1);
      TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
      freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOperatorToken_given_dollar_sign_FFA1point1_with_sign_config_expect_exception_ERROR_INVALID_INTEGER_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   $FFA1.1  "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;  
  Try{
    token = (IntegerToken *)getOperatorToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
      dumpTokenErrorMessage(ex, 1);
      TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
      freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getOperatorToken_given_dollar_sign_D0A1h_with_sign_config_expect_exception_ERROR_INVALID_INTEGER_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   $D0A1h  "); 
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token = NULL;  
  Try{
    token = (IntegerToken *)getOperatorToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
      dumpTokenErrorMessage(ex, 1);
      TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
      freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getStringToken_Hello_how_are_you_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("\"Hello how are you  \""); 
  StringToken *token = NULL;
  Try{
    token = getStringToken(tokenizer);
    TEST_ASSERT_EQUAL(21, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token->type);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    TEST_ASSERT_EQUAL(21, token->length);
    TEST_ASSERT_EQUAL_STRING("\"Hello how are you  \"", token->str);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");       
  }
}

void  test_getStringToken_string_identifier_expect_STRING_STRING_xxx__plus(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("\"STRING_STRING_xxx  +\"hello"); 
  StringToken *token = NULL;
  Try{
    token = getStringToken(tokenizer);
    TEST_ASSERT_EQUAL(22, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token->type);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    TEST_ASSERT_EQUAL(22, token->length);
    TEST_ASSERT_EQUAL_STRING("\"STRING_STRING_xxx  +\"", token->str);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");       
  }
}

void  test_getStringToken_string_identifier_expect_STRING_STRING_xxx_plus(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  \"STRING_STRING_xxx  +\"+ -@# "); 
  StringToken *token = NULL;
  Try{
    token = getStringToken(tokenizer);
    TEST_ASSERT_EQUAL(24, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token->type);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    TEST_ASSERT_EQUAL(22, token->length);
    TEST_ASSERT_EQUAL_STRING("\"STRING_STRING_xxx  +\"", token->str);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");       
  }
}

void  test_getStringToken_hi_12345_expect_hi(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("\"hi\"12345"); 
  StringToken *token = NULL;
  Try{
    token = getStringToken(tokenizer);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token->type);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    TEST_ASSERT_EQUAL(4, token->length);
    TEST_ASSERT_EQUAL_STRING("\"hi\"", token->str);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");       
  }
}

void  test_getStringToken_This_is_a_string_to_test_this_function_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  \"This is a string to test this function.\"   "); 
  StringToken *token = NULL;
  Try{
    token = getStringToken(tokenizer);
    TEST_ASSERT_EQUAL(43, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token->type);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    TEST_ASSERT_EQUAL(41, token->length);
    TEST_ASSERT_EQUAL_STRING("\"This is a string to test this function.\"", token->str);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getStringToken_Hello_comma_abcdeQf_expect_same(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  \"Hello, abcde?f\" "); 
  StringToken *token = NULL;
  Try{
    token = getStringToken(tokenizer);
    TEST_ASSERT_EQUAL(18, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("\"Hello, abcde?f\"", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    TEST_ASSERT_EQUAL(16, token->length);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");         
  }
}

void  test_getStringToken_given_Hello_how_are_you_without_symbol_expect_exception_ERROR_INVALID_STRING_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("\"Hello how are you   "); 
  StringToken *token = NULL;
  Try{
  token = getStringToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_STRING_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
      dumpTokenErrorMessage(ex, 1);
      TEST_ASSERT_EQUAL(ERROR_INVALID_STRING, ex->errorCode);
      freeException(ex);
    }
  freeTokenizer(tokenizer);
}

void  test_getNewlineToken_given_backslash_n_expect_backslash_n_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    \n123  ");   
  Token *token = NULL;
  token = getNewlineToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_NEWLINE_TYPE, token->type);
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  TEST_ASSERT_EQUAL(4, token->startColumn);
  TEST_ASSERT_EQUAL_STRING("\n", token->str);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void  test_getToken_given_NULL_expect_NULL_token_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("      "); 
  Token *token = NULL;
  Try{
    token = getToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE, token->type);
    TEST_ASSERT_EQUAL(6, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");       
  }
}

void  test_getToken_given_backslash_n_expect_NEWLINE_token_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" \n"); 
  Token *token = NULL;
  Try{
    token = getToken(tokenizer);
    TEST_ASSERT_EQUAL(2, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_NEWLINE_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("\n", token->str);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    TEST_ASSERT_EQUAL(1, token->length);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");       
  }
}

void  test_getToken_given_backslasht_backslash_n_expect_NEWLINE_token_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("\t\n   "); 
  Token *token = NULL;
  Try{
    token = getToken(tokenizer);
    TEST_ASSERT_EQUAL(2, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_NEWLINE_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("\n", token->str);
    TEST_ASSERT_EQUAL(1, token->startColumn);
    TEST_ASSERT_EQUAL(1, token->length);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");       
  }
}

void  test_getToken_given_hello123_expect_getIdentifierToken_called_identifier_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("hello123"); 
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("hello123", token0->str);
    TEST_ASSERT_EQUAL(0, token0->startColumn);
    freeToken(token0);
    
    Token *token1 = NULL;     //NULL detected afterwards, therefore return null type
    token1 = getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE, token1->type);
    TEST_ASSERT_NULL(token1->str);
    freeToken(token1);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");   
  }
}

void  test_getToken_given_3030o_backslash_n_with_oct_config_expect_integer_newline_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  3030o\n"); 
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  IntegerToken *token0 = NULL;
  Try{
    token0 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(03030, token0->value);
    TEST_ASSERT_EQUAL_STRING("3030o", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
    
    Token *token1 = NULL;
    token1 = getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_NEWLINE_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("\n", token1->str);
    freeToken(token1);
    
    Token *token2 = NULL;             //NULL detected, therefore return null type
    token2 = getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE, token2->type);
    TEST_ASSERT_NULL(token2->str);
    freeToken(token2);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");   
  }
}

void  test_getToken_given__asdfghjkl_hash_expect_getIdentifierToken_called_identifier_operator_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  _asdfghjkl_# "); 
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(13, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("_asdfghjkl_", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
    
    OperatorToken *token1 = NULL;
    token1 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token1->type);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("#", token1->str);
    TEST_ASSERT_EQUAL(13, token1->startColumn);
    freeToken(token1);
    freeTokenizer(tokenizer);    
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");   
  }
}

void  test_getToken_given_197e2_expect_getFloatToken_called_float_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  197e2  "); 
  FloatToken *token = NULL;
  Try{
    token = (FloatToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(197e2, token->value);
    TEST_ASSERT_EQUAL_STRING("197e2", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");   
  }
}

void  test_getToken_given_34point564_expect_getFloatToken_called_float_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  34.564 "); 
  FloatToken *token = NULL;
  Try{
    token = (FloatToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(34.564, token->value);
    TEST_ASSERT_EQUAL_STRING("34.564", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");   
  }
}

void  test_getToken_given_6135_expect_getDecimalOrFloatToken_called_decimal_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  6135 "); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(6135, token->value);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getToken_given_0456_expect_getOctalToken_called_octal_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   0456 "); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(0456, token->value);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getToken_given_01295_expect_getOctalToken_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   01295 "); 
  IntegerToken *token = NULL;
  Try{
  token = (IntegerToken *)getToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_12x483_expect_getDecimalOrFloatToken_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  12x483 "); 
  IntegerToken *token = NULL;
  Try{
  token = (IntegerToken *)getToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_143eminusx2_expect_getFloatToken_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  143e-x2 "); 
  FloatToken *token = NULL;
  Try{
  token = (FloatToken *)getToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_384point99eplus3u_expect_getFloatToken_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  384.99e+3u "); 
  FloatToken *token = NULL;
  Try{
  token = (FloatToken *)getToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_0b10111_expect_getBinToken_called_bin_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("0b10111"); 
  IntegerToken *token = NULL;
  Try{
    token = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(23, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getToken_given_0b1020_expect_getBinToken_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0b1020 "); 
  IntegerToken *token = NULL;
  Try{
  token = (IntegerToken *)getToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_string_expect_getStringToken_called_string_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  \" 1_3#hello)OPWASD   \" "); 
  StringToken *token = NULL;
  Try{
    token = (StringToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(24, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("\" 1_3#hello)OPWASD   \"", token->str);
    TEST_ASSERT_EQUAL(2, token->startColumn);
    TEST_ASSERT_EQUAL(22, token->length);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getToken_given_string_without_closing_quot_mark_expect_exception_ERROR_INVALID_STRING_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  \"   29#@!(aqijfkskdk   "); 
  StringToken *token = NULL;
  Try{
    token = (StringToken  *)getToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_STRING_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_STRING, ex->errorCode);
    freeException(ex);   
  }
  freeTokenizer(tokenizer);
}


void  test_getToken_given_plus_expect_getOperatorToken_called_operator_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   +-*/"); 
  OperatorToken *token0 = NULL;
  Try{
    token0 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("+", token0->str);
    TEST_ASSERT_EQUAL(3, token0->startColumn);
    freeToken(token0);
    
    OperatorToken *token1 = NULL;
    token1 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("-", token1->str);
    TEST_ASSERT_EQUAL(4, token1->startColumn);
    freeToken(token1);
    
    OperatorToken *token2 = NULL;
    token2 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("*", token2->str);
    TEST_ASSERT_EQUAL(5, token2->startColumn);
    freeToken(token2);
    
    OperatorToken *token3 = NULL;
    token3 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("/", token3->str);
    TEST_ASSERT_EQUAL(6, token3->startColumn);
    freeToken(token3);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");      
  }
}

void  test_getToken_given_different_brackets_expect_getOperatorToken_called_3_operators_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" ( {  [   "); 
  OperatorToken *token0 = NULL;
  Try{
    token0 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token0->type);
    TEST_ASSERT_EQUAL(2, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("(", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
    
    OperatorToken *token1 = NULL;
    token1 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token1->type);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("{", token1->str);
    TEST_ASSERT_EQUAL(3, token1->startColumn);
    freeToken(token1);
    
    OperatorToken *token2 = NULL;
    token2 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("[", token2->str);
    TEST_ASSERT_EQUAL(6, token2->startColumn);
    freeToken(token2);    
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given_different_operators_expect_getOperatorToken_called_7operators_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" ~!@#$%^ "); 
  OperatorToken *token0 = NULL;
  Try{
    token0 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token0->type);
    TEST_ASSERT_EQUAL(2, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("~", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
    
    OperatorToken *token1 = NULL;
    token1 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token1->type);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("!", token1->str);
    TEST_ASSERT_EQUAL(2, token1->startColumn);
    freeToken(token1);
    
    OperatorToken *token2 = NULL;
    token2 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("@", token2->str);
    TEST_ASSERT_EQUAL(3, token2->startColumn);
    freeToken(token2);    
    
    OperatorToken *token3 = NULL;
    token3 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token3->type);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("#", token3->str);
    TEST_ASSERT_EQUAL(4, token3->startColumn);
    freeToken(token3);  

    OperatorToken *token4 = NULL;
    token4 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token4->type);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("$", token4->str);
    TEST_ASSERT_EQUAL(5, token4->startColumn);
    freeToken(token4);        
    
    OperatorToken *token5 = NULL;
    token5 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token5->type);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("%", token5->str);
    TEST_ASSERT_EQUAL(6, token5->startColumn);
    freeToken(token5);    
    
    OperatorToken *token6 = NULL;
    token6 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token6->type);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("^", token6->str);
    TEST_ASSERT_EQUAL(7, token6->startColumn);
    freeToken(token6);    
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given_different_configs_with_all_config_expect_0x103F_0xCDEF_0b10110_0332(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" $103F  CDEFH  10110b  332O ");
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX | TOKENIZER_BIN_B | TOKENIZER_OCT_O | TOKENIZER_HEX_H);
  IntegerToken  *token0 = NULL;
  Try{
    token0 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(0x103F, token0->value);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    TEST_ASSERT_EQUAL_STRING("$103F", token0->str);
    freeToken(token0);
    
    IntegerToken  *token1 = NULL;
    token1 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(13, tokenizer->index);
    TEST_ASSERT_EQUAL(0xCDEF, token1->value);
    TEST_ASSERT_EQUAL(8, token1->startColumn);
    TEST_ASSERT_EQUAL_STRING("CDEFH", token1->str);
    freeToken(token1);
    
    IntegerToken  *token2 = NULL;
    token2 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(21, tokenizer->index);
    TEST_ASSERT_EQUAL(0b10110, token2->value);
    TEST_ASSERT_EQUAL(15, token2->startColumn);
    TEST_ASSERT_EQUAL_STRING("10110b", token2->str);
    freeToken(token2);
    
    IntegerToken  *token3 = NULL;
    token3 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(27, tokenizer->index);
    TEST_ASSERT_EQUAL(0332, token3->value);
    TEST_ASSERT_EQUAL(23, token3->startColumn);
    TEST_ASSERT_EQUAL_STRING("332O", token3->str);
    freeToken(token3);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");       
  }
}

void  test_getToken_given_different_configs_with_all_config_expect_0x099A_0b1100_034_0x99AA(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 099AH 01100b 034 $08AA ");
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX | TOKENIZER_BIN_B | TOKENIZER_OCT_O | TOKENIZER_HEX_H);
  IntegerToken  *token0 = NULL;
  Try{
    token0 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(0x099A, token0->value);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    TEST_ASSERT_EQUAL_STRING("099AH", token0->str);
    freeToken(token0);
    
    IntegerToken  *token1 = NULL;
    token1 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(13, tokenizer->index);
    TEST_ASSERT_EQUAL(0b1100, token1->value);
    TEST_ASSERT_EQUAL(7, token1->startColumn);
    TEST_ASSERT_EQUAL_STRING("01100b", token1->str);
    freeToken(token1);
    
    IntegerToken  *token2 = NULL;
    token2 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(17, tokenizer->index);
    TEST_ASSERT_EQUAL(034, token2->value);
    TEST_ASSERT_EQUAL(14, token2->startColumn);
    TEST_ASSERT_EQUAL_STRING("034", token2->str);
    freeToken(token2);
    
    IntegerToken  *token3 = NULL;
    token3 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(23, tokenizer->index);
    TEST_ASSERT_EQUAL(0x08AA, token3->value);
    TEST_ASSERT_EQUAL(18, token3->startColumn);
    TEST_ASSERT_EQUAL_STRING("$08AA", token3->str);
    freeToken(token3);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");       
  }
}

void  test_getToken_given_different_configs_with_all_config_expect_0x1234_0xCDEF_0b0111_0765_0x1100B(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  01234h CDEFh 0111B 765o 01100BH ");
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX | TOKENIZER_BIN_B | TOKENIZER_OCT_O | TOKENIZER_HEX_H);
  IntegerToken  *token0 = NULL;
  Try{
    token0 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(0x01234, token0->value);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    TEST_ASSERT_EQUAL_STRING("01234h", token0->str);
    freeToken(token0);
    
    IntegerToken  *token1 = NULL;
    token1 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL(0xCDEF, token1->value);
    TEST_ASSERT_EQUAL(9, token1->startColumn);
    TEST_ASSERT_EQUAL_STRING("CDEFh", token1->str);
    freeToken(token1);
    
    IntegerToken  *token2 = NULL;
    token2 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(20, tokenizer->index);
    TEST_ASSERT_EQUAL(0b111, token2->value);
    TEST_ASSERT_EQUAL(15, token2->startColumn);
    TEST_ASSERT_EQUAL_STRING("0111B", token2->str);
    freeToken(token2);
    
    IntegerToken  *token3 = NULL;
    token3 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(25, tokenizer->index);
    TEST_ASSERT_EQUAL(0765, token3->value);
    TEST_ASSERT_EQUAL(21, token3->startColumn);
    TEST_ASSERT_EQUAL_STRING("765o", token3->str);
    freeToken(token3);
    
    IntegerToken  *token4 = NULL;
    token4 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(33, tokenizer->index);
    TEST_ASSERT_EQUAL(0x1100B, token4->value);
    TEST_ASSERT_EQUAL(26, token4->startColumn);
    TEST_ASSERT_EQUAL_STRING("01100BH", token4->str);
    freeToken(token4);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");       
  }
}

void  test_getToken_given__vifhj_plus34_expect__identifier_operator_integer_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    _vifhj+34"); 
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(10, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("_vifhj", token0->str);
    TEST_ASSERT_EQUAL(4, token0->startColumn);
    freeToken(token0);
  
    OperatorToken *token1 = NULL;
    token1 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token1->type);
    TEST_ASSERT_EQUAL(11, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("+", token1->str);
    TEST_ASSERT_EQUAL(10, token1->startColumn);
    freeToken(token1);
  
    IntegerToken  *token2 = NULL;
    token2 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token2->type);
    TEST_ASSERT_EQUAL(13, tokenizer->index);
    TEST_ASSERT_EQUAL(34, token2->value);
    TEST_ASSERT_EQUAL_STRING("34", token2->str);
    TEST_ASSERT_EQUAL(11, token2->startColumn);
    freeToken(token2);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}


void  test_getToken_given_wxyplus_expect_identifier_operator_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   wxy+"); 
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL_STRING("wxy", token0->str);
    TEST_ASSERT_EQUAL(3, token0->startColumn);
    freeToken(token0);
  
    OperatorToken *token1 = NULL;
    token1 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL_STRING("+", token1->str);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(6, token1->startColumn);
    freeToken(token1);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}


void  test_getToken_given_0x349f_hello_plus_312minus4_expect_integer_identifier_operator_integer_operator_integer_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0x349f hello+312-4"); 
  IntegerToken *token0 = NULL;
  Try{
    token0 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL_STRING("0x349f", token0->str);
    TEST_ASSERT_EQUAL(0x349f, token0->value);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
    IdentifierToken *token1 = NULL;
    token1 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("hello", token1->str);
    TEST_ASSERT_EQUAL(13, tokenizer->index);
    TEST_ASSERT_EQUAL(8, token1->startColumn);
    freeToken(token1);
  
    OperatorToken *token2 = NULL;
    token2 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL_STRING("+", token2->str);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL(13, token2->startColumn);
    freeToken(token2);
  
    IntegerToken *token3 = NULL;
    token3 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token3->type);
    TEST_ASSERT_EQUAL(17, tokenizer->index);
    TEST_ASSERT_EQUAL(312, token3->value);
    TEST_ASSERT_EQUAL(14, token3->startColumn);
    freeToken(token3);
  
    OperatorToken *token4 = NULL;
    token4 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token4->type);
    TEST_ASSERT_EQUAL_STRING("-", token4->str);
    TEST_ASSERT_EQUAL(18, tokenizer->index);
    TEST_ASSERT_EQUAL(17, token4->startColumn);
    freeToken(token4);
  
    IntegerToken *token5 = NULL;
    token5 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token5->type);
    TEST_ASSERT_EQUAL(19, tokenizer->index);
    TEST_ASSERT_EQUAL(4, token5->value);
    TEST_ASSERT_EQUAL(18, token5->startColumn);
    freeToken(token5);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given_1947_divide_34point32e_minus2_times_034_minus_0x12_expect_integer_operator_float_operator_integer_operator_integer_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   1947/34.32e-2*034-0x12"); 
  IntegerToken *token0 = NULL;
  Try{
    token0 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL_STRING("1947", token0->str);
    TEST_ASSERT_EQUAL(1947, token0->value);
    TEST_ASSERT_EQUAL(3, token0->startColumn);
    freeToken(token0);
  
    OperatorToken *token1 = NULL;
    token1 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("/", token1->str);
    TEST_ASSERT_EQUAL(7, token1->startColumn);
    freeToken(token1);
  
    FloatToken *token2 = NULL;
    token2 = (FloatToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(16, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token2->type);
    TEST_ASSERT_EQUAL_STRING("34.32e-2", token2->str);
    TEST_ASSERT_EQUAL_FLOAT(34.32e-2, token2->value);
    TEST_ASSERT_EQUAL(8, token2->startColumn);
    freeToken(token2);
  
    OperatorToken *token3 = NULL;
    token3 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(17, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token3->type);
    TEST_ASSERT_EQUAL_STRING("*", token3->str);
    TEST_ASSERT_EQUAL(16, token3->startColumn);
    freeToken(token3);
  
    IntegerToken *token4 = NULL;
    token4 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(20, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token4->type);
    TEST_ASSERT_EQUAL_STRING("034", token4->str);
    TEST_ASSERT_EQUAL(034, token4->value);
    TEST_ASSERT_EQUAL(17, token4->startColumn);
    freeToken(token4);
  
    OperatorToken *token5 = NULL;
    token5 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(21, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token5->type);
    TEST_ASSERT_EQUAL_STRING("-", token5->str);
    TEST_ASSERT_EQUAL(20, token5->startColumn);
    freeToken(token5);
  
    IntegerToken *token6 = NULL;
    token6 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(25, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token6->type);
    TEST_ASSERT_EQUAL_STRING("0x12", token6->str);
    TEST_ASSERT_EQUAL(0x12, token6->value);
    TEST_ASSERT_EQUAL(21, token6->startColumn);
    freeToken(token6);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given_bracket_Identi183__minus0x13_expect_operator_identifier_operator_integer_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  (_Identi183__-0x13 "); 
  OperatorToken *token0 = NULL;
  Try{
    token0 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token0->type);
    TEST_ASSERT_EQUAL_STRING("(", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
  
    IdentifierToken *token1 = NULL;
    token1 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("_Identi183__", token1->str);
    TEST_ASSERT_EQUAL(3, token1->startColumn);
    freeToken(token1);
  
    OperatorToken *token2 = NULL;
    token2 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(16, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL_STRING("-", token2->str);
    TEST_ASSERT_EQUAL(15, token2->startColumn);
    freeToken(token2);
  
    IntegerToken *token3 = NULL;
    token3 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(20, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token3->type);
    TEST_ASSERT_EQUAL_STRING("0x13", token3->str);
    TEST_ASSERT_EQUAL(0x13, token3->value);
    TEST_ASSERT_EQUAL(16, token3->startColumn);
    freeToken(token3);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}
  
  
void  test_getToken_given_String_033_plus_hello_expect_string_integer_operator_identifier_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" \"String Here\"033+hello"); 
  StringToken *token0 = NULL;
  Try{
    token0 = (StringToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token0->type);
    TEST_ASSERT_EQUAL_STRING("\"String Here\"", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
    IntegerToken  *token1 = NULL;
    token1 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(17, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token1->type);
    TEST_ASSERT_EQUAL(033, token1->value);
    TEST_ASSERT_EQUAL_STRING("033", token1->str);
    TEST_ASSERT_EQUAL(14, token1->startColumn);
    freeToken(token1);
  
    OperatorToken *token2 = NULL;
    token2 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(18, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL_STRING("+", token2->str);
    TEST_ASSERT_EQUAL(17, token2->startColumn);
    freeToken(token2);
    
    IdentifierToken *token3 = NULL;
    token3 = (IdentifierToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(23, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token3->type);
    TEST_ASSERT_EQUAL_STRING("hello", token3->str);
    TEST_ASSERT_EQUAL(18, token3->startColumn);
    freeToken(token3);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given_Peace_123plus67_expect_identifier_integer_operator_integer_string_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  Peace  123+67\"school\""); 
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL_STRING("Peace", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
  
    IntegerToken *token1 = NULL;
    token1 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL_STRING("123", token1->str);
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token1->type);
    TEST_ASSERT_EQUAL(123, token1->value);
    TEST_ASSERT_EQUAL(9, token1->startColumn);
    freeToken(token1);
  
    OperatorToken *token2 = NULL;
    token2 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL_STRING("+", token2->str);
    TEST_ASSERT_EQUAL(13, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL(12, token2->startColumn);
    freeToken(token2);
  
    IntegerToken *token3 = NULL;
    token3 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token3->type);
    TEST_ASSERT_EQUAL_STRING("67", token3->str);
    TEST_ASSERT_EQUAL(67, token3->value);
    TEST_ASSERT_EQUAL(13, token3->startColumn);
    freeToken(token3);
  

    StringToken *token = NULL;
    token = (StringToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(23, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("\"school\"", token->str);
    TEST_ASSERT_EQUAL(15, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given_a_string_float_and_invalid_identifier_expect_string_float_returned_exception_ERROR_INVALID_INTEGER_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" \" A string  \"  12.3856e-2  12abc"); 
  StringToken *token0 = NULL;
  Try{
    token0 = (StringToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token0->type);
    TEST_ASSERT_EQUAL_STRING("\" A string  \"", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
    FloatToken *token1 = NULL;
    token1 = (FloatToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(26, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("12.3856e-2", token1->str);
    TEST_ASSERT_EQUAL_FLOAT(12.3856e-2, token1->value);
    TEST_ASSERT_EQUAL(16, token1->startColumn);
    freeToken(token1);

    IntegerToken  *token2 = NULL;
    token2 = (IntegerToken  *)getToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_a_identifier_integer_integer_expect_integer_returned_exception_ERROR_INVALID_INTEGER_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  asdfghjk 0x345_ 12345"); 
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(10, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL_STRING("asdfghjk", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
  
    IntegerToken *token1 = NULL;
    token1 = (IntegerToken  *)getToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_float_and_operator_and_invalid_hex_expect_float_operator_integer_returned_exception_ERROR_INVALID_INTEGER_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 56.395e-3+342 00x34"); 
  FloatToken *token0 = NULL;
  Try{
    token0 = (FloatToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token0->type);
    TEST_ASSERT_EQUAL(10, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("56.395e-3", token0->str);
    TEST_ASSERT_EQUAL_FLOAT(56.395e-3, token0->value);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
    OperatorToken *token1 = NULL;
    token1 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token1->type);
    TEST_ASSERT_EQUAL(11, tokenizer->index);
    TEST_ASSERT_EQUAL(10, token1->startColumn);
    TEST_ASSERT_EQUAL_STRING("+", token1->str);
    freeToken(token1);

    IntegerToken *token2 = NULL;
    token2 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token2->type);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL(342, token2->value);
    TEST_ASSERT_EQUAL_STRING("342", token2->str);
    TEST_ASSERT_EQUAL(11, token2->startColumn);
    freeToken(token2);
  
    IntegerToken  *token3 = NULL;
    token3 = (IntegerToken *)getDecimalOrFloatToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_a_identifier_and_number_and_operator_expect_identifier_number_operator_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" identi 0342af+3  28472fds"); 
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL_STRING("identi", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
  IntegerToken  *token1 = NULL;
  token1 = (IntegerToken  *)getToken(tokenizer);
  TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_identifier_and_hex_and_operator_and_float_expect_identifier_integer_operator_float_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" movwf 0x23+ 1.341e+4"); 
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("movwf", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
    IntegerToken *token1 = NULL;
    token1 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token1->type);
    TEST_ASSERT_EQUAL(0x23, token1->value);
    TEST_ASSERT_EQUAL(11, tokenizer->index);
    TEST_ASSERT_EQUAL(7, token1->startColumn);
    TEST_ASSERT_EQUAL_STRING("0x23", token1->str);
    freeToken(token1);

    OperatorToken *token2 = NULL;
    token2 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("+", token2->str);
    TEST_ASSERT_EQUAL(11, token2->startColumn);
    freeToken(token2);
  
    FloatToken *token3 = NULL;
    token3 = (FloatToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token3->type);
    TEST_ASSERT_EQUAL(21, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(1.341e+4, token3->value);
    TEST_ASSERT_EQUAL_STRING("1.341e+4", token3->str);
    TEST_ASSERT_EQUAL(13, token3->startColumn);
    freeToken(token3);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given__accelerator_148point1323346423eminus2_slash_expect_identifier_float_operator_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   _accelerator_ 148.1323346423e-2/"); 
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(16, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("_accelerator_", token0->str);
    TEST_ASSERT_EQUAL(3, token0->startColumn);
    freeToken(token0);
  
    FloatToken *token1 = NULL;
    token1 = (FloatToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token1->type);
    TEST_ASSERT_EQUAL(34, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(148.1323346423e-2, token1->value);
    TEST_ASSERT_EQUAL_STRING("148.1323346423e-2", token1->str);
    TEST_ASSERT_EQUAL(17, token1->startColumn);
    freeToken(token1);
  
    OperatorToken *token2 = NULL;
    token2 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL(35, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("/", token2->str);
    TEST_ASSERT_EQUAL(34, token2->startColumn);
    freeToken(token2);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown."); 
  }
  
}

void  test_getToken_given_plus_12_String_expect_operator_and_number_returned_exception_ERROR_INVALID_STRING_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  + 12 \" String to test function       ");  
  OperatorToken *token0 = NULL;
  Try{
    token0 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token0->type);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("+", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
  
    IntegerToken *token1 = NULL;
    token1 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token1->type);
    TEST_ASSERT_EQUAL(12, token1->value);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(4, token1->startColumn);
    TEST_ASSERT_EQUAL_STRING("12", token1->str);
    freeToken(token1);

    StringToken  *token2 = NULL;
    token2 = (StringToken  *) getToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_STRING_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_STRING, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_operator_and_invalid_float_and_octal_expect_operator_returned_exception_ERROR_INVALID_FLOAT_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  *18.e0x12 066  ");  
  OperatorToken *token0 = NULL;
  Try{
    token0 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token0->type);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("*", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
  
    FloatToken  *token1 = NULL;
    token1 = (FloatToken  *) getToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);    
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_dot_point_String_expect_operator_indentifier_string_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  .POINT\"A string @183\" ");  
  OperatorToken *token0 = NULL;
  Try{
    token0 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token0->type);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING(".", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
  
    IdentifierToken *token1 = NULL;
    token1 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token1->type);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("POINT", token1->str);
    TEST_ASSERT_EQUAL(3, token1->startColumn);
    freeToken(token1);
  
    StringToken *token2 = NULL;
    token2 = (StringToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token2->type);
    TEST_ASSERT_EQUAL(23, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token2->type);
    TEST_ASSERT_EQUAL_STRING("\"A string @183\"", token2->str);
    TEST_ASSERT_EQUAL(8, token2->startColumn);
    freeToken(token2);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given_Mov_r7_comma_hash_0x0A_expect_indentifier__identifier_operator_operator_integer_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("Mov r7, #0x0A\n");  
  Token *token0 = NULL;
  Try{
    token0 = getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("Mov", token0->str);
    TEST_ASSERT_EQUAL(0, token0->startColumn);
    freeToken(token0);
  
    Token *token1 = NULL;
    token1 = getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token1->type);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("r7", token1->str);
    TEST_ASSERT_EQUAL(4, token1->startColumn);
    freeToken(token1);
  
    Token *token2 = NULL;
    token2 = getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING(",", token2->str);
    TEST_ASSERT_EQUAL(6, token2->startColumn);
    freeToken(token2);
    
    Token *token3 = NULL;
    token3 = getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token3->type);
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("#", token3->str);
    TEST_ASSERT_EQUAL(8, token3->startColumn);
    freeToken(token3);
    
    Token *token4 = NULL;
    token4 = getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token4->type);
    TEST_ASSERT_EQUAL(13, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("0x0A", token4->str);
    TEST_ASSERT_EQUAL(9, token4->startColumn);
    freeToken(token4);
    
    Token *token5 = NULL;
    token5 = getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_NEWLINE_TYPE, token5->type);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("\n", token5->str);
    TEST_ASSERT_EQUAL(13, token5->startColumn);
    freeToken(token5);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given_0x345A_plus_DACBH_divide_166o_with_hex_oct_config_expect_integer_operator_integer_operator_integer_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  0x345A+DACBH/166o ");  
  configureTokenizer(tokenizer, TOKENIZER_HEX_H | TOKENIZER_OCT_O);
  IntegerToken *token0 = NULL;
  Try{
    token0 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(0x345A, token0->value);
    TEST_ASSERT_EQUAL_STRING("0x345A", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
  
    OperatorToken  *token1 = NULL;
    token1 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token1->type);
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("+", token1->str);
    TEST_ASSERT_EQUAL(8, token1->startColumn);
    freeToken(token1);
   
    IntegerToken *token2 = NULL;
    token2 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token2->type);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL(0xDACB, token2->value);
    TEST_ASSERT_EQUAL_STRING("DACBH", token2->str);
    TEST_ASSERT_EQUAL(9, token2->startColumn);
    freeToken(token2);   
 
    OperatorToken  *token3 = NULL;
    token3 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token3->type);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("/", token3->str);
    TEST_ASSERT_EQUAL(14, token3->startColumn);
    freeToken(token3);
    
    IntegerToken *token4 = NULL;
    token4 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token4->type);
    TEST_ASSERT_EQUAL(19, tokenizer->index);
    TEST_ASSERT_EQUAL(0166, token4->value);
    TEST_ASSERT_EQUAL_STRING("166o", token4->str);
    TEST_ASSERT_EQUAL(15, token4->startColumn);
    freeToken(token4);   
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

void  test_getToken_given_10110b_point_0765e_minus_2_with_bin_config_expect_exception_ERROR_INVALID_INTEGER_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  10110b.0765e-2 ");  
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IntegerToken *token0 = NULL;
  Try{
    token0 = (IntegerToken  *)getToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);  
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_is123_plus_4point34e_minus_oplm_expect_identifier_operator_returned_exception_ERROR_INVALID_FLOAT_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   is123 + 4.34e-oplm ");  
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("is123", token0->str);
    TEST_ASSERT_EQUAL(3, token0->startColumn);
    freeToken(token0);
    
    OperatorToken *token1 = NULL;
    token1 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token1->type);
    TEST_ASSERT_EQUAL(10, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("+", token1->str);
    TEST_ASSERT_EQUAL(9, token1->startColumn);
    freeToken(token1);
  
    FloatToken  *token2 = NULL;
    token2 = (FloatToken  *)getToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_FLOAT_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);  
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_identifier_newline_operator_expect_identifier_newline_operator_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("    _yahallo   \n  @ ");  
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("_yahallo", token0->str);
    TEST_ASSERT_EQUAL(4, token0->startColumn);
    freeToken(token0);
    
    Token *token1 = NULL;
    token1 = getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_NEWLINE_TYPE, token1->type);
    TEST_ASSERT_EQUAL(16, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("\n", token1->str);
    TEST_ASSERT_EQUAL(15, token1->startColumn);
    freeToken(token1);
  
    OperatorToken  *token2 = NULL;
    token2 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL(19, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("@", token2->str);
    TEST_ASSERT_EQUAL(18, token2->startColumn);
    freeToken(token2);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");  
  }
}

void  test_getToken_given_0x2345h_equal_12_expect_integer_exception_ERROR_INVALID_INTEGER_is_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0x2345h=12 @(1-2345) ");  
  IntegerToken *token0 = NULL;
  Try{
    token0 = (IntegerToken  *)getToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);  
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_instructions_expect_identifier_operator_identifier_identifier_operator_operator_identifier_operaotr_identifier_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" THERE: 	MOVX A, @DPTR ;comment ");  
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("THERE", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
    
    OperatorToken *token1 = NULL;
    token1 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token1->type);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING(":", token1->str);
    TEST_ASSERT_EQUAL(6, token1->startColumn);
    freeToken(token1);
    
    IdentifierToken *token2 = NULL;
    token2 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token2->type);
    TEST_ASSERT_EQUAL(13, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("MOVX", token2->str);
    TEST_ASSERT_EQUAL(9, token2->startColumn);
    freeToken(token2);
    
    IdentifierToken *token3 = NULL;
    token3 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token3->type);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("A", token3->str);
    TEST_ASSERT_EQUAL(14, token3->startColumn);
    freeToken(token3);    
  
    OperatorToken *token4 = NULL;
    token4 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token4->type);
    TEST_ASSERT_EQUAL(16, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING(",", token4->str);
    TEST_ASSERT_EQUAL(15, token4->startColumn);
    freeToken(token4);

    OperatorToken *token5 = NULL;
    token5 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token5->type);
    TEST_ASSERT_EQUAL(18, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("@", token5->str);
    TEST_ASSERT_EQUAL(17, token5->startColumn);
    freeToken(token5);
    
    IdentifierToken *token6 = NULL;
    token6 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token6->type);
    TEST_ASSERT_EQUAL(22, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("DPTR", token6->str);
    TEST_ASSERT_EQUAL(18, token6->startColumn);
    freeToken(token6);  
    
    OperatorToken *token7 = NULL;
    token7 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token7->type);
    TEST_ASSERT_EQUAL(24, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING(";", token7->str);
    TEST_ASSERT_EQUAL(23, token7->startColumn);
    freeToken(token7);
    
    IdentifierToken *token8 = NULL;
    token8 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token8->type);
    TEST_ASSERT_EQUAL(31, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("comment", token8->str);
    TEST_ASSERT_EQUAL(24, token8->startColumn);
    freeToken(token8);  
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");  
  }
}

void  test_getToken_given_compare123point456O_plus_123DH_with_oct_config_expect_identifier_operator_integer_operator_returned_exception_ERROR_INVALID_INTEGER_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  compare123.456O+ 123Dh@@   (no hex config)");  
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("compare123", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
    
    OperatorToken *token1 = NULL;
    token1 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token1->type);
    TEST_ASSERT_EQUAL(13, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING(".", token1->str);
    TEST_ASSERT_EQUAL(12, token1->startColumn);
    freeToken(token1);
  
    IntegerToken *token2 = NULL;
    token2 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token2->type);
    TEST_ASSERT_EQUAL(17, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("456O", token2->str);
    TEST_ASSERT_EQUAL(0456, token2->value);
    TEST_ASSERT_EQUAL(13, token2->startColumn);
    freeToken(token2);

    OperatorToken *token3 = NULL;
    token3 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token3->type);
    TEST_ASSERT_EQUAL(18, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("+", token3->str);
    TEST_ASSERT_EQUAL(17, token3->startColumn);
    freeToken(token3);
    
    IntegerToken *token4 = NULL;
    token4 = (IntegerToken *)getToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);
  }
  freeTokenizer(tokenizer);
}

void  test_getToken_given_dollarSign_CDCA_parentheses_hash_234_minus_66o_with_oct_config_expect_operator_identifier_operator_operator_integer_operator_integer_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  $CDCA(#234-66o   (No $ config)");  
  configureTokenizer(tokenizer, TOKENIZER_OCT_O);
  OperatorToken *token0 = NULL;
  Try{
    token0 = (OperatorToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token0->type);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("$", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
    
    IdentifierToken *token1 = NULL;
    token1 = (IdentifierToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token1->type);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("CDCA", token1->str);
    TEST_ASSERT_EQUAL(3, token1->startColumn);
    freeToken(token1);
  
    OperatorToken *token2 = NULL;
    token2 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("(", token2->str);
    TEST_ASSERT_EQUAL(7, token2->startColumn);
    freeToken(token2);

    OperatorToken *token3 = NULL;
    token3 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token3->type);
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("#", token3->str);
    TEST_ASSERT_EQUAL(8, token3->startColumn);
    freeToken(token3);
    
    IntegerToken *token4 = NULL;
    token4 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    TEST_ASSERT_EQUAL(234, token4->value);
    TEST_ASSERT_EQUAL_STRING("234", token4->str);
    TEST_ASSERT_EQUAL(9, token4->startColumn);
    freeToken(token4);
    
    OperatorToken *token5 = NULL;
    token5 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token5->type);
    TEST_ASSERT_EQUAL(13, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("-", token5->str);
    TEST_ASSERT_EQUAL(12, token5->startColumn);
    freeToken(token5);
    
    IntegerToken *token6 = NULL;
    token6 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(16, tokenizer->index);
    TEST_ASSERT_EQUAL(066, token6->value);
    TEST_ASSERT_EQUAL_STRING("66o", token6->str);
    TEST_ASSERT_EQUAL(13, token6->startColumn);
    freeToken(token6);    
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown."); 
  }
}

void  test_getToken_given_88AAh_String_10101b_parentheses_dollarSignAAA__with_hex_bin_dollarSign_config_expect_integer_string_integer_operator_integer_returned(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("88AAh\"qazxswedc\"10101b($AAA");  
  configureTokenizer(tokenizer, TOKENIZER_HEX_H | TOKENIZER_BIN_B | TOKENIZER_DOLLAR_SIGN_HEX);
  IntegerToken *token0 = NULL;
  Try{
    token0 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(0X88AA, token0->value);
    TEST_ASSERT_EQUAL_STRING("88AAh", token0->str);
    TEST_ASSERT_EQUAL(0, token0->startColumn);
    freeToken(token0);
    
    StringToken *token1 = NULL;
    token1 = (StringToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token1->type);
    TEST_ASSERT_EQUAL(16, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("\"qazxswedc\"", token1->str);
    TEST_ASSERT_EQUAL(5, token1->startColumn);
    freeToken(token1);
  
    IntegerToken *token2 = NULL;
    token2 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token2->type);
    TEST_ASSERT_EQUAL(22, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("10101b", token2->str);
    TEST_ASSERT_EQUAL(0b10101, token2->value);
    TEST_ASSERT_EQUAL(16, token2->startColumn);
    freeToken(token2);

    OperatorToken *token3 = NULL;
    token3 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token3->type);
    TEST_ASSERT_EQUAL(23, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("(", token3->str);
    TEST_ASSERT_EQUAL(22, token3->startColumn);
    freeToken(token3);
    
    IntegerToken *token4 = NULL;
    token4 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token4->type);
    TEST_ASSERT_EQUAL(27, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("$AAA", token4->str);
    TEST_ASSERT_EQUAL(0xAAA, token4->value);
    TEST_ASSERT_EQUAL(23, token4->startColumn);
    freeToken(token4);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");    
  }
}

void  test_getToken_given_bcf_0x12comma12b_comma_ACCESS_with_bin_config_expect_identifier_integer_returned_exception_ERROR_INVALID_INTEGER_to_be_thrown(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  bcf  0x12, 12b, ACCESS");  
  configureTokenizer(tokenizer, TOKENIZER_BIN_B);
  IdentifierToken *token0 = NULL;
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("bcf", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
    
    IntegerToken *token1 = NULL;
    token1 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token1->type);
    TEST_ASSERT_EQUAL(11, tokenizer->index);\
    TEST_ASSERT_EQUAL(0x12, token1->value);
    TEST_ASSERT_EQUAL_STRING("0x12", token1->str);
    TEST_ASSERT_EQUAL(7, token1->startColumn);
    freeToken(token1);
  
    OperatorToken *token2 = NULL;
    token2 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING(",", token2->str);
    TEST_ASSERT_EQUAL(11, token2->startColumn);
    freeToken(token2);

    IntegerToken *token3 = NULL;
    token3 = (IntegerToken *)getToken(tokenizer);
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);
  }
}

void  test_pushBackToken_given_decimal_expect_token_is_pushed(){
  IntegerToken *token = NULL;
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("   0263   "); 
  Try{
    token = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("0263", token->str);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    TEST_ASSERT_EQUAL(4, token->length);
  
    pushBackToken(tokenizer, (Token *)token);     // Push the token back to tokenizer
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token, ((Token  *)(tokenizer->list->head->data)));
    TEST_ASSERT_EQUAL_STRING("0263", ((Token  *)(tokenizer->list->head->data))->str);
  
    token = (IntegerToken  *)getToken(tokenizer);   //Pop the token from tokenizer
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("0263", token->str);
    TEST_ASSERT_EQUAL(3, token->startColumn);
    TEST_ASSERT_EQUAL(4, token->length);
    freeToken(token);
    freeTokenizer(tokenizer);   
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
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

void  test_pushBackToken_given_decimal_float_identifier_token(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("  1934 3e-2 HIHI   ");  
  IntegerToken  *token0 = NULL;
  Try{
    token0 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
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
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, ((Token  *)(tokenizer->list->head->data))->type);
  
    token0 = (IntegerToken  *)getToken(tokenizer);        //get back same token
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL(1934, token0->value);
    TEST_ASSERT_EQUAL_STRING("1934", token0->str);
    TEST_ASSERT_EQUAL(2, token0->startColumn);
    freeToken(token0);
  
    FloatToken  *token1 = NULL;
    token1 = (FloatToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(11, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token1->type);
    TEST_ASSERT_EQUAL_FLOAT(3e-2, token1->value);
    TEST_ASSERT_EQUAL_STRING("3e-2", token1->str);
    TEST_ASSERT_EQUAL(7, token1->startColumn);
   
    pushBackToken(tokenizer,(Token  *) token1);          //push back token here
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("3e-2", ((Token  *)(tokenizer->list->head->data))->str);
    TEST_ASSERT_EQUAL_STRING("3e-2", ((Token  *)(tokenizer->list->tail->data))->str);
  
    token1 = (FloatToken  *)getToken(tokenizer);      //get back same token
    TEST_ASSERT_EQUAL(11, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token1->type);
    TEST_ASSERT_EQUAL_FLOAT(3e-2, token1->value);
    TEST_ASSERT_EQUAL_STRING("3e-2", token1->str);
    TEST_ASSERT_EQUAL(7, token1->startColumn);
    freeToken(token1);
  
    IdentifierToken *token2 = NULL;
    token2 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(16, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token2->type);
    TEST_ASSERT_EQUAL_STRING("HIHI", token2->str);
    TEST_ASSERT_EQUAL(12, token2->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token2);       //push back token here
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("HIHI", ((Token  *)(tokenizer->list->head->data))->str);
    TEST_ASSERT_EQUAL_STRING("HIHI", ((Token  *)(tokenizer->list->tail->data))->str);
  
    token2 = (IdentifierToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(16, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token2->type);
    TEST_ASSERT_EQUAL_STRING("HIHI", token2->str);
    TEST_ASSERT_EQUAL(12, token2->startColumn);
    freeToken(token2);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}
/*
list            item2     item1     
head ---------->next----->next----------
tail----   |----prev<-----prev         |
count  |   |    token1   token0       NULL
       |  NULL              ^
       |____________________|
*/

void  test_pushBackToken_given_2_continuous_pushbacks(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 123*   ");
  IntegerToken  *token0 = NULL;
  OperatorToken *token1 = NULL;
  Try{
    token0 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL(123, token0->value);
    TEST_ASSERT_EQUAL_STRING("123", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
  
    token1 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("*", token1->str);
    TEST_ASSERT_EQUAL(4, token1->startColumn);
  
    pushBackToken(tokenizer, (Token *)token1);    //Push back
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->head->data);
    pushBackToken(tokenizer, (Token*)token0);     //Push back   
    TEST_ASSERT_EQUAL(1, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token0, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->tail->data);
    freeTokenizer(tokenizer);   //Pushed back tokens will be freed in linkedList
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}

/*
list           item5   item4     item3     item2     item1     
head---------->next---->next---->next----->next----->next---------
tail----     --prev<----prev<----prev<-----prev<-----prev        |
count  |    |  token4   token3   token2    token1    token0    NULL
       |   NULL                                        ^
       |_______________________________________________|
*/

void  test_pushBackToken_given_5_continuous_pushbacks(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" Hello123 0132/1.34e33\"StringHere.Stop\" ");
  IdentifierToken  *token0 = NULL;
  IntegerToken *token1 = NULL;
  OperatorToken *token2 = NULL;
  FloatToken  *token3 = NULL;
  StringToken *token4 = NULL;
  
  Try{
    token0 = (IdentifierToken  *)getToken(tokenizer);   //Obtain token
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("Hello123", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
  
    token1 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL(0132, token1->value);
    TEST_ASSERT_EQUAL_STRING("0132", token1->str);
    TEST_ASSERT_EQUAL(10, token1->startColumn);
  
    token2 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("/", token2->str);
    TEST_ASSERT_EQUAL(14, token2->startColumn);
  
    token3 = (FloatToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(22, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(1.34e33, token3->value);
    TEST_ASSERT_EQUAL_STRING("1.34e33", token3->str);
    TEST_ASSERT_EQUAL(15, token3->startColumn);
  
    token4 = (StringToken *)getToken(tokenizer);
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
  
    token0 = (IdentifierToken  *)getToken(tokenizer);   //pop pushed tokens
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("Hello123", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
    token1 = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL_PTR(token2, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL(0132, token1->value);
    TEST_ASSERT_EQUAL_STRING("0132", token1->str);
    TEST_ASSERT_EQUAL(10, token1->startColumn);
    freeToken(token1);
  
    token2 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL_PTR(token3, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("/", token2->str);
    TEST_ASSERT_EQUAL(14, token2->startColumn);
    freeToken(token2);
  
    token3 = (FloatToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL_PTR(token4, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL(22, tokenizer->index);
    TEST_ASSERT_EQUAL_FLOAT(1.34e33, token3->value);
    TEST_ASSERT_EQUAL_STRING("1.34e33", token3->str);
    TEST_ASSERT_EQUAL(15, token3->startColumn);
    freeToken(token3);
  
    token4 = (StringToken *)getToken(tokenizer);
    TEST_ASSERT_NULL(tokenizer->list->head);
    TEST_ASSERT_EQUAL(39, tokenizer->index);
    TEST_ASSERT_EQUAL_STRING("\"StringHere.Stop\"", token4->str);
    TEST_ASSERT_EQUAL(22, token4->startColumn);
    freeToken(token4);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}


void  test_pushBackToken_given_octal_string_operator(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0231 \"STRING here 1202\" % ");  
  IntegerToken  *token0 = NULL;
  Try{
    token0 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(0231, token0->value);
    TEST_ASSERT_EQUAL_STRING("0231", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
 
    pushBackToken(tokenizer,(Token  *) token0);
    TEST_ASSERT_EQUAL(1, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token0, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token0, tokenizer->list->tail->data);

    token0 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(0231, token0->value);
    TEST_ASSERT_EQUAL_STRING("0231", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
    StringToken *token1 = NULL;
    token1 = (StringToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(24, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("\"STRING here 1202\"", token1->str);
    TEST_ASSERT_EQUAL(6, token1->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token1);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->tail->data);
  
    token1 = (StringToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(24, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("\"STRING here 1202\"", token1->str);
    TEST_ASSERT_EQUAL(6, token1->startColumn);
    freeToken(token1);
  
    OperatorToken *token2 = NULL;
    token2 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(26, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL_STRING("%", token2->str);
    TEST_ASSERT_EQUAL(25, token2->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token2);
    TEST_ASSERT_EQUAL(25, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token2, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token2, tokenizer->list->tail->data);
  
    token2 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(26, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token2->type);
    TEST_ASSERT_EQUAL_STRING("%", token2->str);
    TEST_ASSERT_EQUAL(25, token2->startColumn);
    freeToken(token2);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}


void  test_pushBackToken_given_hexa_operator_float_operator_identifier(){
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(" 0x19E3/12.e-2*index ");  
  IntegerToken  *token0 = NULL;
  Try{
    token0 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(0x19E3, token0->value);
    TEST_ASSERT_EQUAL_STRING("0x19E3", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token0);
    TEST_ASSERT_EQUAL(1, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token0, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token0, tokenizer->list->tail->data);
  
    token0 = (IntegerToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token0->type);
    TEST_ASSERT_EQUAL(0x19E3, token0->value);
    TEST_ASSERT_EQUAL_STRING("0x19E3", token0->str);
    TEST_ASSERT_EQUAL(1, token0->startColumn);
    freeToken(token0);
  
    OperatorToken *token1 = NULL;
    token1 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("/", token1->str);
    TEST_ASSERT_EQUAL(7, token1->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token1);
    TEST_ASSERT_EQUAL(7, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token1, tokenizer->list->tail->data);
  
    token1 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token1->type);
    TEST_ASSERT_EQUAL_STRING("/", token1->str);
    TEST_ASSERT_EQUAL(7, token1->startColumn);
    freeToken(token1);
  
    FloatToken  *token2 = NULL;
    token2 = (FloatToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token2->type);
    TEST_ASSERT_EQUAL(12.e-2, token2->value);
    TEST_ASSERT_EQUAL_STRING("12.e-2", token2->str);
    TEST_ASSERT_EQUAL(8, token2->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token2);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token2, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token2, tokenizer->list->tail->data);
  
    token2 = (FloatToken  *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token2->type);
    TEST_ASSERT_EQUAL(12.e-2, token2->value);
    TEST_ASSERT_EQUAL_STRING("12.e-2", token2->str);
    TEST_ASSERT_EQUAL(8, token2->startColumn);
    freeToken(token2);
  
    OperatorToken *token3 = NULL;
    token3 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token3->type);
    TEST_ASSERT_EQUAL_STRING("*", token3->str);
    TEST_ASSERT_EQUAL(14, token3->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token3);
    TEST_ASSERT_EQUAL(14, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token3, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token3, tokenizer->list->tail->data);
  
    token3 = (OperatorToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token3->type);
    TEST_ASSERT_EQUAL_STRING("*", token3->str);
    TEST_ASSERT_EQUAL(14, token3->startColumn);
    freeToken(token3);
  
    IdentifierToken *token4 = NULL;
    token4 = (IdentifierToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(20, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token4->type);
    TEST_ASSERT_EQUAL_STRING("index", token4->str);
    TEST_ASSERT_EQUAL(15, token4->startColumn);
  
    pushBackToken(tokenizer,(Token  *) token4);
    TEST_ASSERT_EQUAL(15, tokenizer->index);
    TEST_ASSERT_EQUAL_PTR(token4, tokenizer->list->head->data);
    TEST_ASSERT_EQUAL_PTR(token4, tokenizer->list->tail->data);
  
    token4 = (IdentifierToken *)getToken(tokenizer);
    TEST_ASSERT_EQUAL(20, tokenizer->index);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token4->type);
    TEST_ASSERT_EQUAL_STRING("index", token4->str);
    TEST_ASSERT_EQUAL(15, token4->startColumn);
    freeToken(token4);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");     
  }
}
