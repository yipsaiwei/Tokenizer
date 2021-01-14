# Tokenizer
## 1 About This Project
This is a tokenizer that takes in a phrase, sentence, or paragraph and split it into a smaller unit called tokens. The tokens can be integer token, float token, operator token. identifier token, string token, NULL token and new line token. 
Tokenization is important for the system to understand certain instructions or any texts. It is highly used in Natural Language Processing(NLP) where it teaches machines to understand human languages and extract meaning in a complex test.

## 1.1 Objective
To separate a complex text line into its respective tokens.
Example: 
![image](https://user-images.githubusercontent.com/65482031/104545411-f14ce980-5664-11eb-996d-7be0b01a7cde.png)

Each token contains informations such as the length of tokenized strings, type of the token based on the tokenized string and at which column that the tokenized string start.

## 2 Getting started
### 2.1 Software Requirement
To test the program, the following software have to be installed first:
1. Ceedling 
2. MSYS2
3. MINGW
4. Ruby

### 2.2 Clonning the file from GitHub
The program can be clonned by entering the command in GitBash
```
git clone https://github.com/yipsaiwei/Tokenizer
```
An alternative way is to download it through GitHub website if GitBash is not installed in your machine.

## 3 Implementing the function
Below shows how this tokenizer can be used:
```
Tokenizer *tokenizer = NULL;                    //Declare a tokenizer
tokenizer = createTokenizer(" 0264\n#");        //Create a tokenizer with the content wanted to be tokenized
configureTokenizer(tokenizer, TOKENIZER_OCT_O); //Configure tokenizer so that it can recognized certain format of binary, octal and hexadecimal number.
IntegerToken *token = NULL;                     //Declare a token
token = getOctalToken(tokenizer);               //Get token from tokenizer
```
The configureTokenizer function can let the program recognize the format of:
1. Hexadecimal numbers start with dollar sign $ (Default is 0x).
2. Hexadecimal numbers end with h.
3. Octal numbers end with o.
4. Binary numbers end with b.

More informations about the type that can be configured in configureTokenizer functions can refer to the [macro definition here(starts from line 14.)](https://github.com/yipsaiwei/Tokenizer/blob/master/src/Tokenizer.h)

The tokens and tokenizers that are not used should be freed as the memories are allocated dynamically. Below shows how the memories should be freed:
```
freeToken(token);
freeTokenizer(tokenizer);
```

## 4 Testing
## 4.1 Testing the function
To test the Tokenizer, open up GitBash (or alternatively Windows PowerShell/Command Prompt), change the directory to the Tokenizer folder and type the command below:
```
ceedling test:all
```
## 4.2 Adding extra tests
Additional tests can be added. For adding a pass test, the sample code will be as below:
```
void  test_getNumberToken_given_0b1010_expect_getBinToken_called_bin_0b1010(){
  Tokenizer *tokenizer = NULL;                                  //Declare a tokenizer first
  tokenizer = createTokenizer("0b1010");                        //The string/paragraph wanted to be tokenized will be entered here and stored in the tokenizer created
  IntegerToken *token = NULL;                                   //Declare a token with the type that you expect will be returned from the tokenizer
  Try{
    token = (IntegerToken *)getNumberToken(tokenizer);          //Get the token
    TEST_ASSERT_EQUAL(6, tokenizer->index);                     //Compare the data that you expect with the data in the returned token
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token->type);
    TEST_ASSERT_EQUAL(0b1010, token->value);
    TEST_ASSERT_EQUAL(0, token->startColumn);
    freeToken(token);
    freeTokenizer(tokenizer);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);                               //If the test you assumed that it will be passed catch an exception, an error might happen.
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}
```
If error message as below is displayed, it might mean that an invalid number or string is entered, it cannot indetify a vaild token type thus an exception is triggered. The test that you expect it to pass is failed.
![image](https://user-images.githubusercontent.com/65482031/104608599-081f2a80-56bd-11eb-9db5-81c7962636f4.png)

For adding a fail test, the sample code will be as below:
```
void  test_getNumberToken_given_0139_expect_getOctalToken_called_exception_ERROR_INVALID_INTEGER_is_thrown(){
  Tokenizer *tokenizer = NULL;                                //Declare a tokenizer
  tokenizer = createTokenizer("    0139");                    //The string/paragraph wanted to be tokenized will be entered here and stored in the tokenizer created
  IntegerToken *token = NULL;                                 //Declare a token with the type that you expect will be returned from the tokenizer
  Try{
    token = (IntegerToken *)getNumberToken(tokenizer);        //Get the token
    TEST_FAIL_MESSAGE("EXPECT ERROR_INVALID_INTEGER_to_be_thrown, BUT UNRECEIVED");   //If it execute this line, an unperdicted error might happen
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);                             //The error messages in the exception will be dumped and displayed on the screen
    TEST_ASSERT_EQUAL(ERROR_INVALID_INTEGER, ex->errorCode);  //Compare the error type that you expected with the error type in the exception
    freeException(ex);                                        //Don't forget to free the exception at last
  }
  freeTokenizer(tokenizer);                                   //And also free the tokenizer
}
```
If error message as below is displayed, it might mean that the number or string entered is valid, it can identify a vaild token type and the exception is not triggered. 
![image](https://user-images.githubusercontent.com/65482031/104609228-ca6ed180-56bd-11eb-8850-40c217387391.png)

For more test codes, click [here](https://github.com/yipsaiwei/Tokenizer/tree/master/test).
For the list of errors that will cause the tokenizer unable to tokenize, click [here](https://github.com/yipsaiwei/Tokenizer/blob/master/src/Errors.h).

## 5 Results
If all the tests are passed, it means that the program does meet your expectation to some extend.
![image](https://user-images.githubusercontent.com/65482031/104610883-75cc5600-56bf-11eb-9120-2953f97a1c95.png)
It also do show the test outputs; the messages thrown by exception in the tests that you expect it to fail.
![image](https://user-images.githubusercontent.com/65482031/104611212-d8255680-56bf-11eb-85f2-1b9139742171.png)
