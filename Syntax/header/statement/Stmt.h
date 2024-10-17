//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_STMT_H
#define COMPILER_STMT_H

#include "../statement.h"
class Stmt : public statement {
public:
    std::unique_ptr<ASTnode> Expression;
    Stmt(std::unique_ptr<ASTnode> exp):Expression(std::move(exp)){}
    void getNode() override{
        std::cout<<"return"<<" ";
        if (Expression)
        Expression->getNode();
        std::cout<<";"<<" ";
    }
};


#endif //COMPILER_STMT_H
