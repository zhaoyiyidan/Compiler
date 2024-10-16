//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_STMT_H
#define COMPILER_STMT_H

#include "../statement.h"
class Stmt : public statement {
public:
    std::string keyword="return";
    std::unique_ptr<ASTnode> exp;
    Stmt(std::unique_ptr<ASTnode> exp):exp(std::move(exp)){}
};


#endif //COMPILER_STMT_H
