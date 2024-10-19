//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_ASSIGNSTMT_H
#define COMPILER_ASSIGNSTMT_H

#include "../statement.h"
#include "../Declaration/VarDecl.h"
class AssignStmt : public statement {
public:
std::unique_ptr<ASTnode> variable;
std::unique_ptr<ASTnode> expression;
AssignStmt(std::unique_ptr<ASTnode> variable, std::unique_ptr<ASTnode> expression):variable(std::move(variable)),expression(std::move(expression)){}
    void getNode() override{

    }
};


#endif //COMPILER_ASSIGNSTMT_H
