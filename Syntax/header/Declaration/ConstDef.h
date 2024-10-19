//
// Created by 赵鲲翔 on 2024/10/19.
//

#ifndef COMPILER_CONSTDEF_H
#define COMPILER_CONSTDEF_H

#include "../Declaration.h"
#include "iostream"
class ConstDef: public Declaration {
public:
    std::string identifier;
    std::unique_ptr<ASTnode> expression;// which is a const value
    ConstDef(std::string identifier, std::unique_ptr<ASTnode> expression): identifier(std::move(identifier)), expression(std::move(expression)){}
    void getNode() override{
        std::cout<< "ConstDef: {";
        std::cout<<identifier;
        expression->getNode();
        std::cout << "}";
    }
};


#endif //COMPILER_CONSTDEF_H
