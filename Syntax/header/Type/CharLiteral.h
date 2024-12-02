//
// Created by 赵鲲翔 on 2024/10/14.
//
// not use
#ifndef COMPILER_CHARLITERAL_H
#define COMPILER_CHARLITERAL_H

#include "../Type.h"
class CharLiteral : public Type{
public:
    char value;
    CharLiteral(char value): value(value){}
    void getNode() override{

    }
    std::string GetNodeType() override{
        return "CharLiteral";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
    virtual llvm::Value* codeGen(CodeGenContext& context) override;
};


#endif //COMPILER_CHARLITERAL_H
