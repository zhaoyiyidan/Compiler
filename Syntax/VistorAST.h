//
// Created by 赵鲲翔 on 2024/10/28.
//

#ifndef COMPILER_VISTORAST_H
#define COMPILER_VISTORAST_H

class VistorAST {
public:
    virtual void visit(const class ConstDecl &node) = 0;
    virtual void visit(const class ConstDef &node) = 0;
    virtual void visit(const class Decl &node) = 0;
    virtual void visit(const class FunctionDec &node) = 0;
    virtual void visit(const class VarDecl &node) = 0;
    virtual void visit(const class VarDef &node) = 0;
    virtual void visit(const class AddExp &node) = 0;
    virtual void visit(const class AssignStmt &node) = 0;
    virtual void visit(const class BinaryOperator &node) = 0;
    virtual void visit(const class compoundstmt &node) = 0;
    virtual void visit(const class EqExp &node) = 0;
    virtual void visit(const class Expression &node) = 0;
    virtual void visit(const class LAndExp &node) = 0;
    virtual void visit(const class LOrExp &node) = 0;
    virtual void visit(const class MulExp &node) = 0;
    virtual void visit(const class PrimaryExp &node) = 0;
    virtual void visit(const class RelExp &node) = 0;
    virtual void visit(const class ReturnStmt &node) = 0;
    virtual void visit(const class UnaryExp &node) = 0;
    virtual void visit(const class UnaryOp &node) = 0;
    virtual void visit(const class IntegerLiteral &node) = 0;
    virtual void visit(const class Number &node) = 0;
    virtual void visit(const class BoolLiteral &node) = 0;
    virtual void visit(const class CharLiteral &node) = 0;
    virtual void visit(const class FloatLiteral &node) = 0;
    virtual void visit(const class FunctionType &node) = 0;
    virtual void visit(const class IFStmt &node) = 0;
    virtual void visit(const class WhileStmt &node) = 0;
    virtual void visit(const class ForStmt &node) = 0;
    virtual void visit(const class LValue &node) = 0;
    virtual void visit(const class BreakStmt &node) = 0;
    virtual void visit(const class ContinueStmt &node) = 0;
    virtual void visit(const class EXP &node) = 0;
};


#endif //COMPILER_VISTORAST_H
