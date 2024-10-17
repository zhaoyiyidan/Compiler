//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_EQEXP_H
#define COMPILER_EQEXP_H

#include "../statement.h"
class EqExp :public statement{
public:
    std::unique_ptr<ASTnode> expression;// EqExp or RelExp
    std::string op;//"==" or "!="
    std::unique_ptr<ASTnode> RelExp;// it must be a RelExp
    // expression "==" "=!" RelExp
    EqExp(std::unique_ptr<ASTnode> expression,std::unique_ptr<ASTnode> RelExp,std::string op ):op(op),expression(std::move(expression)),RelExp(std::move(RelExp)){}
    void getNode() override{
        if (expression)
        expression->getNode();
        std::cout<<op;
        if(RelExp)
        RelExp->getNode();
    }

};


#endif //COMPILER_EQEXP_H
