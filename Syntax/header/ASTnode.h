//
// Created by 赵鲲翔 on 2024/10/14.
//

#ifndef COMPILER_ASTNODE_H
#define COMPILER_ASTNODE_H
#include <memory>
#include <iostream>
class ASTnode {
public:
      virtual void getNode()=0;// print the node
     // virtual ~ASTnode() = default;
};


#endif //COMPILER_ASTNODE_H
