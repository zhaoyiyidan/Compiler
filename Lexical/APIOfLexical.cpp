//
// Created by 赵鲲翔 on 2024/10/11.
//

#include "APIOfLexical.h"
#include <iostream>
#include <set>
#include <string>
using namespace std;

string keyWord[25]= {"void", "int", "char", "float", "double", "bool", \
                   "long", "short", "signed", "unsigned",\
                   "const", "inline",\
                   "for", "while", "if", "else",\
                   "switch", "case", "default", "break", "continue", "return",\
                   "main", "include",\
                   "struct"};
char whitespace[] = {' ', '\t', '\n', '\r'};

//There is only one single operator, '~'
char doubleOperator[] = {'+', '-', '*', '/', '%', '=', '!', '>', '<', '&', '|', '^'};

//There are two others: ' and ", cannot be written in the array
char delimiter[] = {'(', ')', '[', ']', '{', '}', '.', ',', ';', '?', '#'};

// set<pair<int, string> > output;


// Declare the position and peek of the dealing input
bool isKeyWord(string word) {
    for (int i = 0; i < 25; i ++) {
        if (word == keyWord[i]) {
            return true;
        }
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
    return (ch >= 'A' && ch <= 'z');

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



void dealWithLetter(string& input, int& pos, char peek) {
    string str = "";
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

    if (isKeyWord(str)) {
        cout << "Keyword " << str << endl;
    } else {
        cout << "Identifier " << str << endl;
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
            if (peek == '.') {
                type = "double";
            }
            str += peek;
            pos += 1;
            peek = input[pos];
        }
    }
    cout << "double " << str << endl;
}

void dealWithOperator(string& input, int& pos, char peek) {
    if (peek == '~' || pos >= input.length()) {
        cout << "Operator ~" << endl;
        return;
    }

    //Deal with the double operator
    char next = input[pos + 1];
    if (next == '=') {
        cout << "Operator" << peek << "=" << endl;
        pos ++;
    } else if (next == peek) {
        cout << "Operator" << peek << peek << endl;
        pos ++;
    } else {
        cout << "Operator" << peek << endl;
    }
    pos ++;
    return;
}

void dealWithDelimiter(int& pos, char peek) {
    pos += 1;
    cout << "Delimiter " << peek << endl;
}


void words(string input) {
    int pos;
    char peek;
    while (pos <= input.length() - 1) {
        peek = input[pos];
        if (isWhiteSpace(peek)) {pos += 1;}
        else if (isLetter(peek)) {
            dealWithLetter(input, pos, peek);
        } else if (isDigit(peek)) {
            dealWithDigit(input, pos, peek);
        } else if (isOperator(peek)) {
            dealWithOperator(input, pos, peek);
        } else if (isDelimiter(peek)) {
            dealWithDelimiter(pos, peek);
        }
    }
}

int main() {
    // string filename;
    // ifstream file;
    // file.open(filename.c_str())

    // int ch;
    // while (ch = infile.get() != EOF) {
    //     words();
    // }

    string input;
    cout << "Please input the string: ";

    cin >> input;

    words(input);
        // file.close();


    return 0;
}
