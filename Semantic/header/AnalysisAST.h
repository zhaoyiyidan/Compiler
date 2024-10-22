//
// Created by 赵鲲翔 on 2024/10/21.
//

#ifndef COMPILER_ANALYSISAST_H
#define COMPILER_ANALYSISAST_H
#include "SymbolTable.h"
#include "../../Syntax/header/ASTnode.h"
#include "../../Syntax/header/module.h"
// question i need to access the variable in each node,but i only have the pointer to paraent.
static SymbolTable AnalysisAST(const module &node);
static void AnalysisFuncDef(const std::unique_ptr<ASTnode> &node, SymbolTable &table);
static void AnalysisBlock(const std::unique_ptr<ASTnode> &node, SymbolTable &table);
static void AnalysisStatement(const std::unique_ptr<ASTnode> &node, SymbolTable &table);
static void AnalysisConstDef(const std::unique_ptr<ASTnode> &node, SymbolTable &table);
static void AnalysisVarDef(const std::unique_ptr<ASTnode> &node, SymbolTable &table);
static void AnalysisExpression(const std::unique_ptr<ASTnode> &node, SymbolTable &table);
static void AnalysisAssignStatement(const std::unique_ptr<ASTnode> &node, SymbolTable &table);

#endif //COMPILER_ANALYSISAST_H
