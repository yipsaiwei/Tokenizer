#include "unity.h"
#include  "Tokenizer.h"
#include "TokenizerExceptionThrowing.h"
#include "Token.h"
#include "Exception.h"
#include "CException.h"
#include  "DoubleLinkedList.h"
#include  "MemAlloc.h"

CEXCEPTION_T ex;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_integerExceptionThrowing()
{
  Try{
    integerExceptionThrowing("  10293dfg ", 2, "Just to test integerExceptionThrowing function"); 
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);        
  }
}

void test_integerExceptionThrowing_end_with_backslash_t()
{
  Try{
    integerExceptionThrowing("  19191tt\t@@@@@@@@@@@@ ", 2, "Just to test integerExceptionThrowing function with backslash t"); 
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);
    freeException(ex);        
  }
}

void test_floatExceptionThrowing()
{
  Try{
    floatExceptionThrowing("    34.555.4 ", 4, "Just to test floatExceptionThrowing function"); 
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);        
  }
}

void test_floatExceptionThrowing_end_with_backslash_t()
{
  Try{
    floatExceptionThrowing("   12e--3\t#### ", 3, "Just to test floatExceptionThrowing function with backslash t"); 
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FLOAT, ex->errorCode);
    freeException(ex);        
  }
}

void test_stringExceptionThrowing()
{
  Try{
    stringExceptionThrowing("   \"A string..... ", 3, "Just to test stringExceptionThrowing function"); 
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERROR_INVALID_STRING, ex->errorCode);
    freeException(ex);        
  }
}
