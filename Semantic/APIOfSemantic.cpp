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
// change the symbol table and the analysis
void TheAnalysis(ASTnode *node, Analysis &Theanalysis){
    if (Theanalysis.symbolTable.scopeStack.empty()){
    Theanalysis.symbolTable.EnterScope();// intialize the symbol table
    }
    node->accept(Theanalysis);
}

