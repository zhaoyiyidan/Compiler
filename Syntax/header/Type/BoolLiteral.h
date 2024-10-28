//
// Created by 赵鲲翔 on 2024/10/14.
//

#ifndef COMPILER_BOOLLITERAL_H
#define COMPILER_BOOLLITERAL_H

#include "../Type.h"
class BoolLiteral: public Type{
public:
    bool value;
    BoolLiteral(bool value): value(value){}
    void getNode() override{

    }
    std::string GetNodeType() override{
        return "BoolLiteral";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_BOOLLITERAL_H
