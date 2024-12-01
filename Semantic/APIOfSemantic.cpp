//
// Created by 赵鲲翔 on 2024/10/29.
//

#include "APIOfSemantic.h"
SymbolTable analysis(const module &node){
    Analysis analysis;
    analysis.symbolTable.EnterScope();
    for (auto &node:node.Node){
        node->accept(analysis);
    }
    return analysis.symbolTable;
}
SymbolTable analysis(ASTnode *node){
    Analysis analysis;
    analysis.symbolTable.EnterScope();
    node->accept(analysis);
    return analysis.symbolTable;
}
void analysis(ASTnode *node, SymbolTable& sym){
    Analysis analysis;
    analysis.symbolTable=sym;
    analysis.symbolTable.EnterScope();
    node->accept(analysis);
    sym=analysis.symbolTable;
}
