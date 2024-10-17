//
// Created by 赵鲲翔 on 2024/10/14.
//

#ifndef COMPILER_RETURNSTMT_H
#define COMPILER_RETURNSTMT_H

#include "../statement.h"
class ReturnStmt: public statement{
public:
    std::unique_ptr<ASTnode> expression;
    ReturnStmt(std::unique_ptr<ASTnode> expression):expression(std::move(expression)){}
    void getNode() override{

    }
};


#endif //COMPILER_RETURNSTMT_H
