//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_ASSIGNSTMT_H
#define COMPILER_ASSIGNSTMT_H

#include "../statement.h"
#include "../Declaration/VarDecl.h"
class AssignStmt : public statement {
public:
std::string identifier;
std::unique_ptr<ASTnode> expression;
AssignStmt(std::string variable, std::unique_ptr<ASTnode> expression):identifier(std::move(variable)),expression(std::move(expression)){}
    void getNode() override{
        std::cout<< identifier<<"=";
        expression->getNode();
        std::cout<<";"<<std::endl;
    }
    std::string GetNodeType() override{
        return "AssignStmt";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
    virtual llvm::Value* codeGen(CodeGenContext& context) override;
};


#endif //COMPILER_ASSIGNSTMT_H
