# I/O
the input is a cpp file ,the output is a vector of strings that contains the tokens of the file
you need to implement the function vector<string> getTokens(string file) in the file Lexical.cpp
# the getTokens function
this function takes a file name that contains the path of the cpp file and returns a vector of strings that contains the tokens of the file
for example,getTokens("main.cpp") should return a vector of strings that contains the tokens of the file main.cpp
# the tokens
the pair in the vector should be in the form of {type, token},
for example if the token is a keyword the pair should be {"KeyWord", "int"}
if the token is an identifier the pair should be {"IDEN", "x"}
if the token is a const value the pair should be {"NUM", "5"} or {"NUM", "5.5"}
if the token is a string the pair should be {"STR", "hello"}
if the token is a char the pair should be {"CHAR", "a"}
if the token is an operator the pair should be {"OP", "+"}
if the token is a separator the pair should be {"SEP", ";"} , {"SEP", "{"} , {"SEP", "}"} , {"SEP", "("} , {"SEP", ")"}
if the token is "cout" or "cin“, the pair should be {"Input", "cin"}, {"Output", "cout"}
# Test
your function should pass the test in the TestDirectory

