//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_VARDECL_H
#define COMPILER_VARDECL_H
#include "../Declaration.h"
#include "string"
#include "iostream"
class VarDecl: public Declaration {
public:
    std::string NodeType="VarDecl";
    std::unique_ptr<ASTnode> type;
    std::unique_ptr<ASTnode> VarDef;
    std::vector<std::unique_ptr<ASTnode>> VarDefs;
    VarDecl(std::unique_ptr<ASTnode> type, std::unique_ptr<ASTnode> VarDef): type(std::move(type)), VarDef(std::move(VarDef)){}
    VarDecl(std::unique_ptr<ASTnode> type, std::unique_ptr<ASTnode> VarDef, std::vector<std::unique_ptr<ASTnode> > VarDefs): type(std::move(type)), VarDef(std::move(VarDef)), VarDefs(std::move(VarDefs)){}
    void getNode() override{
        std::cout<< "VarDecl: {"<<std::endl;
        type->getNode();
        std::cout << std::endl;
        VarDef->getNode();
        for(auto &i: VarDefs){
            if (i)
            i->getNode();
        }
        std::cout << "}";
    }
    std::string GetNodeType() override{
        return NodeType;
    }
};


#endif //COMPILER_VARDECL_H
