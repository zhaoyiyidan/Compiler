//
// Created by 赵鲲翔 on 2024/10/15.
//
// not use
#ifndef COMPILER_EXPRESSION_H
#define COMPILER_EXPRESSION_H

#include "../statement.h"
class Expression: public statement {
public:
    std::string nodetype="Expression";
    std::unique_ptr<ASTnode> expression;// LOrExp
    Expression(std::unique_ptr<ASTnode> expression):expression(std::move(expression)){}
    void getNode() override{
        if (expression)
        expression->getNode();
    }
    std::string GetNodeType() override{
        return "Expression";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_EXPRESSION_H
