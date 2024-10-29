//
// Created by 赵鲲翔 on 2024/10/14.
//

#ifndef COMPILER_ASTNODE_H
#define COMPILER_ASTNODE_H
#include <memory>
#include <iostream>
#include "../VistorAST.h"
class ASTnode{
public:
    virtual ~ASTnode() = default;
    virtual void getNode()=0;// print the node
    virtual std::string GetNodeType()=0;// get the type of the node
    virtual void accept(VistorAST &vistor)=0;
     // virtual ~ASTnode() = default;
};


#endif //COMPILER_ASTNODE_H
