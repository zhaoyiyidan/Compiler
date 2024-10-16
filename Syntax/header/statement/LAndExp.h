//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_LANDEXP_H
#define COMPILER_LANDEXP_H

#include "../statement.h"
class LAndExp :public statement{
public:
    std::unique_ptr<ASTnode> expression;// LAndExp "&&" EqExp
    std::string op="&&";
    std::unique_ptr<ASTnode> EqExp;// it must be a EqExp
    // expression && EqExp
    LAndExp(std::unique_ptr<ASTnode> expression,std::unique_ptr<ASTnode> EqExp):expression(std::move(expression)),EqExp(std::move(EqExp)){}
};


#endif //COMPILER_LANDEXP_H
