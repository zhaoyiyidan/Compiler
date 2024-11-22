//
// Created by 赵鲲翔 on 2024/10/15.
//
// not use
#ifndef COMPILER_UNARYOP_H
#define COMPILER_UNARYOP_H

#include "../statement.h"
class UnaryOp: public statement{
public:
    std::string op;// "+" "-" "!"
    UnaryOp(std::string op):op(op){}
    void getNode() override{
        std::cout<<op;
    }
    std::string GetNodeType() override{
        return "UnaryOp";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
    virtual llvm::Value* codeGen(CodeGenContext& context) override;
};


#endif //COMPILER_UNARYOP_H
