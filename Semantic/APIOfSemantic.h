//
// Created by 赵鲲翔 on 2024/10/29.
//

#ifndef COMPILER_APIOFSEMANTIC_H
#define COMPILER_APIOFSEMANTIC_H
#include "header/SymbolTable.h"
#include "Analysis.h"
#include "../Syntax/header/module.h"
SymbolTable analysis(const module &node);
SymbolTable analysis(ASTnode *node);


#endif //COMPILER_APIOFSEMANTIC_H
