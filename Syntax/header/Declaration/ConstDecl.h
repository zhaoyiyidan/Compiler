//
// Created by 赵鲲翔 on 2024/10/19.
//

#ifndef COMPILER_CONSTDECL_H
#define COMPILER_CONSTDECL_H

#include "../Declaration.h"
#include "iostream"
class ConstDecl: public Declaration {
public:
    std::string NodeType="ConstDecl";
    std::unique_ptr<ASTnode> type;
    std::unique_ptr<ASTnode> ConstDef;
    std::vector<std::unique_ptr<ASTnode>> ConstDefs;
    ConstDecl(std::unique_ptr<ASTnode> type, std::unique_ptr<ASTnode> ConstDef): type(std::move(type)), ConstDef(std::move(ConstDef)){}
    ConstDecl(std::unique_ptr<ASTnode> type,std::unique_ptr<ASTnode> ConstDef, std::vector<std::unique_ptr<ASTnode>> ConstDefs): type(std::move(type)),ConstDef(std::move(ConstDef)), ConstDefs(std::move(ConstDefs)){}
    void getNode() override{
        std::cout<< "ConstDecl: {"<<std::endl;
        std::cout << "   type: ";
        type->getNode();
        std::cout << std::endl;
        ConstDef->getNode();
        for(auto &i: ConstDefs){
            if (i)
                std::cout<<std::endl;
            i->getNode();
        }
        std::cout << "}"<<std::endl;
    }
    std::string GetNodeType() override{
        return NodeType;
    }
};


#endif //COMPILER_CONSTDECL_H
