//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_MODULE_H
#define COMPILER_MODULE_H
// this file needed
#include "vector"
#include "Declaration.h"
#include "statement.h"
#include "Type.h"
#include <string>
// this is a module, it is the root of the AST
// it contains all the other classes
#include "memory"
class module {
public:
    std::vector<std::unique_ptr<ASTnode> > Node;
    void getNode(){
        for (const auto& node:Node){
            node->getNode();
        }
    }
};


#endif //COMPILER_MODULE_H
