//
// Created by 赵鲲翔 on 2024/10/15.
//
// not use
#ifndef COMPILER_UNARYEXP_H
#define COMPILER_UNARYEXP_H

#include "../statement.h"
class UnaryExp: public statement{
public:
    std::unique_ptr<ASTnode> expression;// UnaryOp
    std::unique_ptr<ASTnode> unaryExp;// it must be a UnaryExp
    UnaryExp(std::unique_ptr<ASTnode> expression,std::unique_ptr<ASTnode> unaryExp):expression(std::move(expression)),unaryExp(std::move(unaryExp)){}
    void getNode() override{
        if (expression)
        expression->getNode();
        if (unaryExp)
        unaryExp->getNode();
    }
    std::string GetNodeType() override{
        return "UnaryExp";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
    virtual llvm::Value* codeGen(CodeGenContext& context) override;
};


#endif //COMPILER_UNARYEXP_H
