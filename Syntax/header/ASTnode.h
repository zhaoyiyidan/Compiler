//
// Created by 赵鲲翔 on 2024/10/14.
//

#ifndef COMPILER_ASTNODE_H
#define COMPILER_ASTNODE_H
#include <memory>
#include <iostream>
#include "CodeGenContext.h"
class ASTnode{
public:
    virtual ~ASTnode() = default;
    virtual void getNode()=0;// print the node
    virtual std::string GetNodeType()=0;// get the type of the node
     // virtual ~ASTnode() = default;
    virtual llvm::Value* codeGen(CodeGenContext& context) = 0;
};


#endif //COMPILER_ASTNODE_H
