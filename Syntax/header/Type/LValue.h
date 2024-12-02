//
// Created by 赵鲲翔 on 2024/10/30.
//
// not use
#ifndef COMPILER_LVALUE_H
#define COMPILER_LVALUE_H

#include "../Type.h"
class LValue: public Type{
public:
    std::string name;
    LValue(std::string name): name(name){}
    void getNode() override{
        std::cout<<name;
    }
    std::string GetNodeType() override{
        return "LValue";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
    virtual llvm::Value* codeGen(CodeGenContext& context) override;
};


#endif //COMPILER_LVALUE_H
