//
// Created by 赵鲲翔 on 2024/10/15.
//
// not use
#ifndef COMPILER_LOREXP_H
#define COMPILER_LOREXP_H

#include "../statement.h"
class LOrExp: public statement{
public:
    std::unique_ptr<ASTnode> expression;// LOrExp may exist
    std::string op="||";
    std::unique_ptr<ASTnode> LAndExp;// it must be a LAndExp
    // expression || LAndExp
    LOrExp(std::unique_ptr<ASTnode> expression,std::unique_ptr<ASTnode> LAndExp):expression(std::move(expression)),LAndExp(std::move(LAndExp)){}
    void getNode() override{
        if (expression)
        expression->getNode();
        std::cout<<"||";
        if (LAndExp)
        LAndExp->getNode();
    }
    std::string GetNodeType() override{
        return "LOrExp";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
    virtual llvm::Value* codeGen(CodeGenContext& context) override;
};


#endif //COMPILER_LOREXP_H
