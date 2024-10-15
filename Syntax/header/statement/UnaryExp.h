//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_UNARYEXP_H
#define COMPILER_UNARYEXP_H

#include "../statement.h"
class UnaryExp {
public:
    std::unique_ptr<ASTnode> expression;// UnaryOp or PrimaryExp
    std::unique_ptr<ASTnode> UnaryExp;// it must be a UnaryExp
};


#endif //COMPILER_UNARYEXP_H
