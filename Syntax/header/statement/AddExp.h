//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_ADDEXP_H
#define COMPILER_ADDEXP_H

#include "../statement.h"
class AddExp: public statement{
public:
    std::unique_ptr<ASTnode> expression;// AddExp or MulExp
    char op;// "+" "-"
    std::unique_ptr<ASTnode> MulExp;// it must be a MulExp
};


#endif //COMPILER_ADDEXP_H
