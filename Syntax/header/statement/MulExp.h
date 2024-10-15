//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_MULEXP_H
#define COMPILER_MULEXP_H

#include "../statement.h"
class MulExp {
public:
    std::unique_ptr<ASTnode> expression;// MulExp or UnaryExp
    char op;// "*" "/"
    std::unique_ptr<ASTnode> UnaryExp;// it must be a UnaryExp
};


#endif //COMPILER_MULEXP_H
