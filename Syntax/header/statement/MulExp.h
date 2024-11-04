//
// Created by 赵鲲翔 on 2024/10/15.
//
// not use
#ifndef COMPILER_MULEXP_H
#define COMPILER_MULEXP_H

#include "../statement.h"
class MulExp: public statement{
public:
    std::unique_ptr<ASTnode> expression;// MulExp
    std::string op;// "*" "/" "%"
    std::unique_ptr<ASTnode> UnaryExp;// it must be a UnaryExp
    MulExp(std::unique_ptr<ASTnode> expression,std::unique_ptr<ASTnode> UnaryExp,std::string op):expression(std::move(expression)),op(op),UnaryExp(std::move(UnaryExp)){}
    void getNode() override{
        if (expression)
        expression->getNode();
        std::cout<<op;
        if (UnaryExp)
        UnaryExp->getNode();
    }
    std::string GetNodeType() override{
        return "MulExp";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_MULEXP_H
