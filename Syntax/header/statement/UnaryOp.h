//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_UNARYOP_H
#define COMPILER_UNARYOP_H

#include "../statement.h"
class UnaryOp: public statement{
public:
    std::string op;// "+" "-" "!"
    UnaryOp(std::string op):op(op){}
    void getNode() override{
        std::cout<<op;
    }
    std::string GetNodeType() override{
        return "UnaryOp";
    }
};


#endif //COMPILER_UNARYOP_H
