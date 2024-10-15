//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_LOREXP_H
#define COMPILER_LOREXP_H

#include "../statement.h"
class LOrExp: public statement{
public:
    std::unique_ptr<ASTnode> expression;// LOrExp "||" LAndExp
    char op='||';
    std::unique_ptr<ASTnode> LAndExp;// it must be a LAndExp
    // expression || LAndExp
    LOrExp(std::unique_ptr<ASTnode> expression):expression(std::move(expression)){}
};


#endif //COMPILER_LOREXP_H
