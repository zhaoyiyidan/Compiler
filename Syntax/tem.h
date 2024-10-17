//
// Created by 赵鲲翔 on 2024/10/16.
//

#ifndef COMPILER_TEM_H
#define COMPILER_TEM_H

#include "iostream"
#include "Source/ConstructAST.cpp"
using namespace std;
int main(){
    cout << "Hello, World!" << endl;

    std::vector<std::pair<std::string,std::string>> tokens;
    tokens.push_back(std::make_pair("int","int"));
    tokens.push_back(std::make_pair("main","main"));
    tokens.push_back(std::make_pair("(","("));
    tokens.push_back(std::make_pair(")",""));
    tokens.push_back(std::make_pair("{","{"));
    tokens.push_back(std::make_pair("int","return"));
    tokens.push_back(std::make_pair("0","1"));
    tokens.push_back(std::make_pair(";","+"));
    tokens.push_back(std::make_pair("}","2"));
    tokens.push_back(std::make_pair("}","*"));
    tokens.push_back(std::make_pair("}","3"));
    tokens.push_back(std::make_pair("}",";"));
    tokens.push_back(std::make_pair("}","}"));
    ConstructAST a;
    auto b=a.ConstructMoule(tokens);
    b.getNode();
    return 0;
}


#endif //COMPILER_TEM_H
