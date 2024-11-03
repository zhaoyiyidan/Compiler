//
// Created by 赵鲲翔 on 2024/10/29.
//

#ifndef COMPILER_IFSTMT_H
#define COMPILER_IFSTMT_H

#include "../statement.h"
class IFStmt :public statement{
public:
    std::unique_ptr<ASTnode> condition;// the condition of the if statement
    std::unique_ptr<ASTnode> body;// the body of the if statement which is a compound statement
    std::unique_ptr<ASTnode> else_body;// which may not exist, "else if " see it as a new if statement "else" see it as a compound statement
    IFStmt(std::unique_ptr<ASTnode> condition,std::unique_ptr<ASTnode> body,std::unique_ptr<ASTnode> else_body):condition(std::move(condition)),body(std::move(body)),else_body(std::move(else_body)){}
    void getNode() override{
        std::cout<<"if";
        if (condition)
            std::cout<<"(";
            condition->getNode();
            std::cout<<")";
        if (body)
            body->getNode();
        if (else_body){
            else_body->getNode();
        }
    }
    std::string GetNodeType() override{
        return "IFStmt";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_IFSTMT_H
