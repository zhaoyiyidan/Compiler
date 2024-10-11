//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_EXPRESSION_H
#define COMPILER_EXPRESSION_H

#include "../statement.h"
#include "BinaryOperator.h"
#include "../Type/Constvalue.h"
class expression: public statement{
public:
    expression* left;
    BinaryOperator* op;
    expression* right;
    Constvalue* value;
};


#endif //COMPILER_EXPRESSION_H
