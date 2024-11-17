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
    // add support for array
    std::unique_ptr<ASTnode> array_size;
    std::vector< std::unique_ptr<ASTnode> > array;

    VarDef(std::string identifier, std::unique_ptr<ASTnode> expression): identifier(std::move(identifier)), expression(std::move(expression)){}
    VarDef(std::string identifier, std::unique_ptr<ASTnode> expression, std::unique_ptr<ASTnode> array_size, std::vector< std::unique_ptr<ASTnode> > array): identifier(std::move(identifier)), expression(std::move(expression)), array_size(std::move(array_size)), array(std::move(array)){}

    void getNode() override{
        std::cout<< identifier;
        if (expression) {
            std::cout << " = ";
            expression->getNode();
        }
        if (array_size) {
            std::cout << " [";
            array_size->getNode();
            std::cout << "]";
        }
        if (!array.empty()) {
            std::cout << " = {";
            for (int i = 0; i < array.size(); i++) {
                array[i]->getNode();
                if (i != array.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "}";
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
