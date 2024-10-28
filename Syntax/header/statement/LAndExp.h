//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_LANDEXP_H
#define COMPILER_LANDEXP_H

#include "../statement.h"
class LAndExp :public statement{
public:
    std::unique_ptr<ASTnode> expression;// LAndExp
    std::string op="&&";
    std::unique_ptr<ASTnode> EqExp;// it must be a EqExp
    // expression && EqExp
    LAndExp(std::unique_ptr<ASTnode> expression,std::unique_ptr<ASTnode> EqExp):expression(std::move(expression)),EqExp(std::move(EqExp)){}
    void getNode() override{
        if (expression)
        expression->getNode();
        std::cout<<"&&";
        if (EqExp)
        EqExp->getNode();
    }
    std::string GetNodeType() override{
        return "LAndExp";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_LANDEXP_H
