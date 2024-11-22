//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_STATEMENT_H
#define COMPILER_STATEMENT_H

#include <vector>
#include <string>
#include "ASTnode.h"
class statement:public ASTnode {
public:
    // search algorithm
    // this function is used to search the tree depending on the order you want to iterate
    // you can search in pre in post order
     void getNode() override{}

    std::string GetNodeType() override{
        return "statement";
    }
    void accept(VistorAST &vistor) override {

    }
    virtual llvm::Value* codeGen(CodeGenContext& context) override;
};


#endif //COMPILER_STATEMENT_H
