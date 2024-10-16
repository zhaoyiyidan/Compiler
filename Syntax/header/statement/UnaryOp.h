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
};


#endif //COMPILER_UNARYOP_H
