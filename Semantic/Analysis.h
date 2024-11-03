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

     void visit(const class Number &node) override;
     void visit(const class BoolLiteral &node) override;
     void visit(const class CharLiteral &node) override;
     void visit(const class FloatLiteral &node) override;
     void visit(const class ConstDef &node) override ;
     void visit(const class Decl &node) override;
     void visit(const class VarDef &node) override;
     void visit(const class AddExp &node) override;
     void visit(const class AssignStmt &node) override;
     void visit(const class BinaryOperator &node) override;
     void visit(const class EqExp &node) override;
     void visit(const class Expression &node) override;
     void visit(const class LAndExp &node) override;
     void visit(const class LOrExp &node) override;
     void visit(const class MulExp &node) override;
     void visit(const class PrimaryExp &node) override;
     void visit(const class RelExp &node) override;
     void visit(const class ReturnStmt &node) override;
     void visit(const class UnaryExp &node) override;
     void visit(const class UnaryOp &node) override;
     void visit(const class IntegerLiteral &node) override;
     void visit(const class FunctionType &node) override;
      void visit(const class IFStmt &node) override;
     void visit(const class WhileStmt &node) override;
     void visit(const class ForStmt &node) override;
     void visit(const class LValue &node) override;
     void visit(const class BreakStmt &node) override;
     void visit(const class ContinueStmt &node) override;
     void visit(const class EXP &node) override;
    double applyOp(const std::string& op, double a, double b);
    double calculate(const class EXP &node);

};


#endif //COMPILER_ANALYSIS_H
