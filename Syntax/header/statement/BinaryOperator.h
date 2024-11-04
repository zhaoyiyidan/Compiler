//
// Created by 赵鲲翔 on 2024/10/11.
//
// not use
#ifndef COMPILER_BINARYOPERATOR_H
#define COMPILER_BINARYOPERATOR_H

#include "../statement.h"
class BinaryOperator: public statement {
public:
    char op;// "+","-","*","/","%"
    std::unique_ptr<ASTnode> left;
    std::unique_ptr<ASTnode> right;
    BinaryOperator(char op, std::unique_ptr<ASTnode> left, std::unique_ptr<ASTnode> right):op(op),left(std::move(left)),right(std::move(right)){}
    void getNode() override{

    }
    std::string GetNodeType() override{
        return "BinaryOperator";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_BINARYOPERATOR_H
