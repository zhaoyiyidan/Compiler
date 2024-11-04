//
// Created by 赵鲲翔 on 2024/10/15.
//
// not use
#ifndef COMPILER_NUMBER_H
#define COMPILER_NUMBER_H

#include "../statement.h"
class Number : public statement{
public:
    std::unique_ptr<ASTnode> number;// it is constant value,many be integerLiteral or floatLiteral or charLiteral ...
    void getNode() override{}
    std::string GetNodeType() override{
        return "Number";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_NUMBER_H
