//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_DECLARATION_H
#define COMPILER_DECLARATION_H

#include <vector>
#include <string>
#include "ASTnode.h"
class Declaration :public ASTnode{
public:

void getNode() override{

    }
    std::string GetNodeType() override{
        return "Declaration";
    }
    void accept(VistorAST &vistor) override {

    }
};


#endif //COMPILER_DECLARATION_H
