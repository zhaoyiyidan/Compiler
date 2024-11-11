//
// Created by 赵鲲翔 on 2024/10/29.
//

#ifndef COMPILER_APIOFSEMANTIC_H
#define COMPILER_APIOFSEMANTIC_H
#include "header/SymbolTable.h"
#include "Analysis.h"
#include "../Syntax/header/module.h"
SymbolTable analysis(const module &node){
    Analysis analysis;
    analysis.symbolTable.EnterScope();
    for (auto &node:node.Node){
        node->accept(analysis);
    }
    return analysis.symbolTable;
}




#endif //COMPILER_APIOFSEMANTIC_H
