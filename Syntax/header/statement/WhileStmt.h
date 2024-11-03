//
// Created by 赵鲲翔 on 2024/10/29.
//

#ifndef COMPILER_WHILESTMT_H
#define COMPILER_WHILESTMT_H

#include "../statement.h"
class WhileStmt :public statement{
public:
    std::unique_ptr<ASTnode> condition;// the condition of the while loop
    std::unique_ptr<ASTnode> body;// the body of the while loop which is a compound statement
    WhileStmt(std::unique_ptr<ASTnode> condition,std::unique_ptr<ASTnode> body):condition(std::move(condition)),body(std::move(body)){}
    void getNode() override{
        std::cout<<"While";
        if (condition)
            std::cout<<"(";
            condition->getNode();
            std::cout<<")";
        if (body)
            body->getNode();
    }
    std::string GetNodeType() override{
        return "WhileStmt";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_WHILESTMT_H
