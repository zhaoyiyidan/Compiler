//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_RETURNSTMT_H
#define COMPILER_RETURNSTMT_H

#include "../statement.h"
class ReturnStmt : public statement {
public:
    std::unique_ptr<ASTnode> Expression;
    ReturnStmt(std::unique_ptr<ASTnode> exp): Expression(std::move(exp)){}
    void getNode() override{
        std::cout<<"return"<<" ";
        if (Expression)
        Expression->getNode();
        std::cout<<";"<<" ";
    }
    std::string GetNodeType() override{
        return "ReturnStmt";
    }
};


#endif //COMPILER_RETURNSTMT_H
