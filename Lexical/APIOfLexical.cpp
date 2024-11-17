//
// Created by 马宸泽 on 2024/10/21.
//

#include "APIOfLexical.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <filesystem>
using namespace std;

// Global variable for lexical
vector<pair<string,string> > output;

// Global variable for comment
bool hasBeenComment = false;

// Global variable for error
bool hasError = false;
int row = 1;

struct Error {
    int row;       //The row of the error
    string message;     //Report what is the kind of the error
};

void error(bool& hasError, string errorMessage, int row) {
    Error error1;
    hasError = true;
    error1.message = errorMessage;
    error1.row = row;
}

void getpair(string first, string second) {
    pair<string, string> answer;
    answer.first = first;
    answer.second = second;
    output.push_back(answer);
}

string keyWord[28]= {"void", "int", "char", "float", "double", "bool", "string" \
                   "long", "short", "signed", "unsigned",\
                   "const", "inline",\
                   "for", "while", "if", "else",\
                   "switch", "case", "default", "break", "continue", "return",\
                   "main",\
                   "struct",\
                   "std", \
                   "using", "namespace", "std"};

char whitespace[] = {' ', '\t', '\n', '\r'};

//There is only one single operator, '~'
char doubleOperator[] = {'+', '-', '*', '/', '%', '=', '!', '>', '<', '&', '|', '^'};

//There are two others: ' and ", cannot be written in the array
char delimiter[] = {'(', ')', '[', ']', '{', '}', '.', ',', ';', '?', '#', ':'};



// Declare the position and peek of the dealing input
bool isKeyWord(string word) {
    for (const auto & i : keyWord) {
        if (word == i) {
            return true;
        }
    }

    return false;
}

bool isComment(string& input, int pos, char peek,bool& hasBeenComment) {
    int length = input.size();
    if (length == 1) {
        if (hasBeenComment) {
            return true;
        } else {
            return false;
        }
    }
    char next = input[pos + 1];
    char last = input[length - 1];
    char ll = input[length - 2];
    if (peek == '/' && next == '/') {
        return true;
    } else if (peek == '/' && next == '*') {

        if (!(last == '/' && ll == '*')) {
            hasBeenComment = true;
        }
        return true;
    } else if (hasBeenComment) {
        if (last == '/' && ll == '*') {
            hasBeenComment = false;
        }
        return true;
    }

    return false;
}

bool isWhiteSpace(char ch) {
    for (int i = 0; i < 4; i ++) {
        if (ch == whitespace[i]) {
            return true;
        }
    }
    return false;
}

bool isLetter(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return true;
    } else if (ch >= 'a' && ch <= 'z') {
        return true;
    } else if (ch == '_') {
        return true;
    }
    return false;

}

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

bool isOperator(char ch) {
    if (ch == '~') {
        return true;
    }

    for (int i = 0; i < 12; i++) {
        if (ch == doubleOperator[i]) {
            return true;
        }
    }
    return false;
}

bool isDelimiter(char ch) {
    for (int i = 0; i < 11; i++) {
        if (ch == delimiter[i]) {
            return true;
        }
    }
    return false;
}

bool isString(char ch) {
    return (ch == '"');
}

bool isChar(char ch) {
    return (ch == '\'');
}

void singleGetToken(string& absolutePath);
string findFileInParentDirectory(const std::string& fileName);

void dealWithInclude(string& input, int& pos, string& absolutePath) {
    char peek = input[pos];
    while (peek != '\"') {
        pos++;
        peek = input[pos];
    }

    pos++;
    peek = input[pos];

    string str;
    while (isLetter(peek) || isDigit(peek)) {
        if (pos >= input.length()) {
            pos += 1;
            break;
        } else {
            str += peek;
            pos += 1;
            peek = input[pos];
        }
    }

    str += ".cpp";
    string curr = findFileInParentDirectory(str);
    if (curr != absolutePath) {
        singleGetToken(curr);
    }

}

void dealWithLetter(string& input, int& pos, char peek, bool& isInclude, string& absolutePath) {
    string str;
    while (isLetter(peek) || isDigit(peek)) {
        if (pos >= input.length()) {
            pos += 1;
            break;
        }
        str += peek;
        pos += 1;
        peek = input[pos];
    }

    if (str == "include") {
        isInclude = true;
        dealWithInclude(input, pos, absolutePath);
        return;
    }

    if (isKeyWord(str)) {
        getpair("KeyWord", str);
    } else if (str == "true" || str == "false") {
        getpair("BoolLiteral", str);
    } else if (str == "cout") {
        getpair("Output", str);
    } else if (str == "cin") {
        getpair("Input", str);
    } else {
        getpair("IDEN", str);
    }
}

void dealWithDigit(string& input, int& pos, char peek) {
    string str = "";
    string type = "int";
    while (isDigit(peek) || peek == '.') {
        if (pos >= input.length()) {
            pos += 1;
            break;
        } else {
            str += peek;
            pos += 1;
            peek = input[pos];
        }
    }
    getpair("NUM", str);
}

void dealWithOperator(string& input, int& pos, char peek) {
    string str;
    str += peek;
    if (peek == '~' || pos >= input.length()) {
        getpair("OP", "~");
        pos += 1;
        return;
    }

    //Deal with the double operator
    char next = input[pos + 1];
    if (next == '=' && pos != input.size()) {
        str += "=";
        getpair("OP", str);
        pos ++;
    } else if (next == peek && pos != input.size()) {
        str += peek;
        getpair("OP", str);
        pos ++;
    } else {
        getpair("OP", str);
    }
    pos ++;
}

void dealWithDelimiter(int& pos, char peek) {
    pos += 1;
    string str;
    str += peek;
    if (str != "#") {
        getpair("SEP", str);
    }
}

void dealWithString(string&input, int&pos, char peek) {
    string str = "";
    if (pos == input.size() - 1) {
        string message = "You can't put \" at the end of the line.";
        error(hasError, message, row);
        return;
    }
    pos++;
    peek = input[pos];
    while (peek != '"') {
        str += peek;
        pos += 1;
        peek = input[pos];
    }
    pos += 1;
    getpair("STR", str);
}

void dealWithChar(string&input, int&pos, char peek) {
    string str = "";
    str += input[pos + 1];
    if (pos == input.size() || input[pos + 2] != '\'') {
        string message = "There cannot be two characters in a char. ";
        error(hasError, message, row);
        return;
    }
    pos += 3;
    getpair("CHAR", str);
}


void words(string input, bool& hasBeenComment, bool& hasError, int row, string& absolutePath) {
    if (input.length() == 0) {
        return;
    }
    bool isInclude;
    int pos = 0;
    char peek;
    while (pos <= input.length() - 1) {
        peek = input[pos];
        if (isWhiteSpace(peek)) {pos += 1;}
        else if (isComment(input, pos, peek, hasBeenComment)) {
            return;
        } else if (isLetter(peek)) {
            dealWithLetter(input, pos, peek, isInclude, absolutePath);
        } else if (isDigit(peek)) {
            dealWithDigit(input, pos, peek);
        } else if (isOperator(peek)) {
            dealWithOperator(input, pos, peek);
        } else if (isDelimiter(peek)) {
            dealWithDelimiter(pos, peek);
        } else if (isString(peek)) {
            dealWithString(input, pos, peek);
        } else if (isChar(peek)) {
            dealWithChar(input, pos, peek);
        }
        if (hasError || isInclude) {
            break;
        }
    }
}


string findFileInParentDirectory(const std::string& fileName) {
    try {
        filesystem::path currentPath = filesystem::current_path();
        filesystem::path parentPath = currentPath.parent_path();

        filesystem::path targetFilePath = parentPath / fileName;
        if (filesystem::exists(targetFilePath) && filesystem::is_regular_file(targetFilePath)) {
            filesystem::current_path(parentPath);
            return filesystem::absolute(targetFilePath).string();
        }

        filesystem::path targetFileInCurrent = currentPath / fileName;
        if (filesystem::exists(targetFileInCurrent) && filesystem::is_regular_file(targetFileInCurrent)) {
            filesystem::current_path(currentPath);
            return filesystem::absolute(targetFileInCurrent).string();
        }

        throw std::runtime_error("File not found in both current and parent directories");

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return "";
    }
}

void singleGetToken(string& absolutePath) {
    string line;
    ifstream file(absolutePath);
    if (!file.is_open()) {
        std::cerr << "Have error opening:  " << absolutePath << std::endl;
        return;
    }
    while (getline(file, line)) {
        words(line, hasBeenComment, hasError, row, absolutePath);
        if (hasError) {break;}
        row++;
    }
    file.close();

}

vector<pair<string,string> > gettoken(const string& filename) {
    string absolutePath = findFileInParentDirectory(filename);
    singleGetToken(absolutePath);
    return output;
}
