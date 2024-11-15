//
// Created by 赵鲲翔 on 2024/10/19.
//

#ifndef COMPILER_CONSTDEF_H
#define COMPILER_CONSTDEF_H

#include "../Declaration.h"
#include "iostream"
class ConstDef: public Declaration {
public:
    std::string NodeType="ConstDef";
    std::string identifier;
    std::unique_ptr<ASTnode> expression;// which is a const value
    // add support for array
    std::unique_ptr<ASTnode> array_size;
    std::vector< std::unique_ptr<ASTnode> > array;
    ConstDef(std::string identifier, std::unique_ptr<ASTnode> expression): identifier(std::move(identifier)), expression(std::move(expression)){}
    ConstDef(std::string identifier, std::unique_ptr<ASTnode> expression, std::unique_ptr<ASTnode> array_size, std::vector< std::unique_ptr<ASTnode> > array): identifier(std::move(identifier)), expression(std::move(expression)), array_size(std::move(array_size)), array(std::move(array)){}

    void getNode() override{
        std::cout<<identifier<<" : ";
        expression->getNode();
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
        return NodeType;
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_CONSTDEF_H
