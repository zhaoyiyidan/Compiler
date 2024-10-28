//
// Created by 赵鲲翔 on 2024/10/21.
//

#include "../header/AnalysisAST.h"
#include "../../Syntax/APIOfSyntax.h"
static SymbolTable AnalysisAST(const module &node) {
    SymbolTable table;
    for (const auto &i : node.Node) {
        AnalysisFuncDef(i, table);
    }
}
static void AnalysisFuncDef(const std::unique_ptr<ASTnode> &node, SymbolTable &table) {

}
