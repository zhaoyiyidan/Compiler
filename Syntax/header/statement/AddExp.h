//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_ADDEXP_H
#define COMPILER_ADDEXP_H

#include "../statement.h"
class AddExp: public statement{
public:
    std::unique_ptr<ASTnode> expression;// AddExp
    std::string op;// "+" "-"
    std::unique_ptr<ASTnode> MulExp;// it must be a MulExp
    AddExp(std::unique_ptr<ASTnode> expression,std::unique_ptr<ASTnode> MulExp,std::string op):expression(std::move(expression)),op(op),MulExp(std::move(MulExp)){}
    void getNode() override{
        if (expression)
        expression->getNode();
        std::cout<<op;
        if (MulExp)
        MulExp->getNode();
    }
    std::string GetNodeType() override{
        return "AddExp";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_ADDEXP_H
