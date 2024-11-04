//
// Created by 赵鲲翔 on 2024/10/14.
//
// not use
#ifndef COMPILER_INTEGERLITERAL_H
#define COMPILER_INTEGERLITERAL_H

#include "../Type.h"
class IntegerLiteral: public Type{
public:
    int value;
    IntegerLiteral(std::string value): value(std::stoi(value)){}
     void getNode() override{
        std::cout<<value;
    }
    std::string GetNodeType() override{
        return "IntegerLiteral";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_INTEGERLITERAL_H
