//
// Created by 赵鲲翔 on 2024/10/28.
//

#ifndef COMPILER_ANALYSIS_H
#define COMPILER_ANALYSIS_H

#include "../Syntax/VistorAST.h"
#include "header/SymbolTable.h"

class Analysis:public VistorAST{
public:
  SymbolTable symbolTable;
  void visit(const class FunctionDec &node) override;
  void visit(const class compoundstmt &node) override;
  void visit(const class VarDecl &node) override;
  void visit(const class ConstDecl &node) override;
};


#endif //COMPILER_ANALYSIS_H
