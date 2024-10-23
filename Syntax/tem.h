//
// Created by 赵鲲翔 on 2024/10/16.
//

#ifndef COMPILER_TEM_H
#define COMPILER_TEM_H

#include "iostream"
#include "Source/ConstructAST.cpp"
#include "header/HelperFunction.h"
using namespace std;
int main(){

    cout << "Hello, World!" << endl;

    std::vector<std::pair<std::string,std::string>> tokens;
    tokens.push_back(std::make_pair("keyword","int"));
    tokens.push_back(std::make_pair("keyword","main"));
    tokens.push_back(std::make_pair("(","("));
    tokens.push_back(std::make_pair(")",")"));
    tokens.push_back(std::make_pair("{","{"));
    tokens.push_back(std::make_pair("keyword","return"));
    tokens.push_back(std::make_pair("0","1"));
    tokens.push_back(std::make_pair(";","+"));
    tokens.push_back(std::make_pair("}","2"));
    tokens.push_back(std::make_pair("}","*"));
    tokens.push_back(std::make_pair("}","3"));
    tokens.push_back(std::make_pair("}",";"));
    tokens.push_back(std::make_pair("}","}"));
    ConstructAST a;
    // auto b=a.ConstructMoule(tokens);
    // b.getNode();
    std::vector<std::pair<std::string,std::string>> tokens1;
    tokens1.push_back(std::make_pair("KeyWord","int"));
    tokens1.push_back(std::make_pair("main","main"));
    tokens1.push_back(std::make_pair("(","("));
    tokens1.push_back(std::make_pair(")",")"));
    tokens1.push_back(std::make_pair("{","{"));
    tokens1.push_back(std::make_pair("KeyWord","const"));
    tokens1.push_back(std::make_pair("int","int"));
    tokens1.push_back(std::make_pair("IDEN","x"));
    tokens1.push_back(std::make_pair("=","="));
    tokens1.push_back(std::make_pair("Integer","233"));
    tokens1.push_back(std::make_pair(";","*"));
    tokens1.push_back(std::make_pair("KeyWord","4"));
    tokens1.push_back(std::make_pair("k",";"));
    tokens1.push_back(std::make_pair("KeyWord","return"));
    tokens1.push_back(std::make_pair("0","1"));
    tokens1.push_back(std::make_pair(";","+"));
    tokens1.push_back(std::make_pair("}","2"));
    tokens1.push_back(std::make_pair("}","*"));
    tokens1.push_back(std::make_pair("}","3"));
    tokens1.push_back(std::make_pair("}",";"));
    tokens1.push_back(std::make_pair("KeyWord","int"));
    tokens1.push_back(std::make_pair("IDEN","X"));
    tokens1.push_back(std::make_pair("=","="));
    tokens1.push_back(std::make_pair("NUM","233"));
    tokens1.push_back(std::make_pair(";","*"));
    tokens1.push_back(std::make_pair("NUM","4"));
    tokens1.push_back(std::make_pair(";",";"));
    tokens1.push_back(std::make_pair("KeyWord","int"));
    tokens1.push_back(std::make_pair("IDEN","b"));
    tokens1.push_back(std::make_pair("=",";"));
    tokens1.push_back(std::make_pair("IDEN","b"));
    tokens1.push_back(std::make_pair(";","="));
    tokens1.push_back(std::make_pair("IDEN","10"));
    tokens1.push_back(std::make_pair(";",";"));

    tokens1.push_back(std::make_pair("}","}"));
    auto c=a.ConstructMoule(tokens1);
    c.getNode();
    return 0;

}


#endif //COMPILER_TEM_H
