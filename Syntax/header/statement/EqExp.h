//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_EQEXP_H
#define COMPILER_EQEXP_H

#include "../statement.h"
class EqExp :public statement{
public:
    std::unique_ptr<ASTnode> expression;// EqExp or RelExp
    char op1='==';
    char op2='!=';
    std::unique_ptr<ASTnode> RelExp;// it must be a RelExp
    // expression "==" "=!" RelExp
    EqExp(std::unique_ptr<ASTnode> expression):expression(std::move(expression)){}
};


#endif //COMPILER_EQEXP_H
