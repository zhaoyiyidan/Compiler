//
// Created by 赵鲲翔 on 2024/10/19.
//
// not use
#ifndef COMPILER_DECL_H
#define COMPILER_DECL_H

#include "../Declaration.h"
#include "iostream"
class Decl: public Declaration {
public:

    void getNode() override{

    }
    std::string GetNodeType() override{
        return "Decl";
    }
    void accept(VistorAST &vistor) override {

    }
    virtual llvm::Value* codeGen(CodeGenContext& context) override;
};


#endif //COMPILER_DECL_H
