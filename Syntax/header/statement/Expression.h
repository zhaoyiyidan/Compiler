//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_EXPRESSION_H
#define COMPILER_EXPRESSION_H

#include "../statement.h"
class Expression {
public:
    std::unique_ptr<ASTnode> expression;// LOrExp
    Expression(std::unique_ptr<ASTnode> expression):expression(std::move(expression)){}
};


#endif //COMPILER_EXPRESSION_H
