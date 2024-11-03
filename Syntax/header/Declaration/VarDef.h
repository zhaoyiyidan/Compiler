//
// Created by 赵鲲翔 on 2024/10/19.
//

#ifndef COMPILER_VARDEF_H
#define COMPILER_VARDEF_H

#include "../Declaration.h"
#include "iostream"
#include "string"
class VarDef: public Declaration {
public:
    std::string identifier;
    std::unique_ptr<ASTnode> expression;
    VarDef(std::string identifier, std::unique_ptr<ASTnode> expression): identifier(std::move(identifier)), expression(std::move(expression)){}
    void getNode() override{
        std::cout<< identifier;
        if (expression) {
            std::cout << " = ";
            expression->getNode();
        }
    }
    std::string GetNodeType() override{
        return "VarDef";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_VARDEF_H
