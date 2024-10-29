//
// Created by 赵鲲翔 on 2024/10/29.
//

#ifndef COMPILER_FORSTMT_H
#define COMPILER_FORSTMT_H

#include "../statement.h"
class ForStmt :public statement{
public:
    std::unique_ptr<ASTnode> init;// which is a varibale declaration
    std::unique_ptr<ASTnode> condition;// the condition of the for loop
    std::unique_ptr<ASTnode> increment;// the increment of the for loop
    std::unique_ptr<ASTnode> body;// the body of the for loop which is a compound statement
    ForStmt(std::unique_ptr<ASTnode> init,std::unique_ptr<ASTnode> condition,std::unique_ptr<ASTnode> increment,std::unique_ptr<ASTnode> body):init(std::move(init)),condition(std::move(condition)),increment(std::move(increment)),body(std::move(body)){}
    void getNode() override{
        if (init)
            init->getNode();
        if (condition)
            condition->getNode();
        if (increment)
            increment->getNode();
        if (body)
            body->getNode();
    }
    std::string GetNodeType() override{
        return "ForStmt";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_FORSTMT_H
