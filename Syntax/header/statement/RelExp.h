//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_RELEXP_H
#define COMPILER_RELEXP_H

#include "../statement.h"
class RelExp:public statement {
public:
    std::unique_ptr<ASTnode> expression;// AddExp or RelExp
    char op;// "<" "<=" ">" ">="
    std::unique_ptr<ASTnode> AddExp;// it must be a AddExp
};


#endif //COMPILER_RELEXP_H
