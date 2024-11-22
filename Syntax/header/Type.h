//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_TYPE_H
#define COMPILER_TYPE_H

#include <vector>
#include <string>
#include "ASTnode.h"
class Type: public ASTnode{
public:
void getNode() override{

}
    std::string GetNodeType() override{
        return "Type";
    }
    void accept(VistorAST &vistor) override {

    }
    virtual llvm::Value* codeGen(CodeGenContext& context) override;
};


#endif //COMPILER_TYPE_H
