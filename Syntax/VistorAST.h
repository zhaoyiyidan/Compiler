//
// Created by 赵鲲翔 on 2024/10/28.
//

#ifndef COMPILER_VISTORAST_H
#define COMPILER_VISTORAST_H


class VistorAST {
public:
    virtual void visit(class ConstDecl &node) = 0;
    virtual void visit(class ConstDef &node) = 0;
    virtual void visit(class Decl &node) = 0;
    virtual void visit(class FunctionDec &node) = 0;
    virtual void visit(class VarDecl &node) = 0;
    virtual void visit(class VarDef &node) = 0;
    virtual void visit(class AddExp &node) = 0;
    virtual void visit(class AssignStmt &node) = 0;
    virtual void visit(class BinaryOperator &node) = 0;
    virtual void visit(class compoundstmt &node) = 0;
    virtual void visit(class EqExp &node) = 0;
    virtual void visit(class Expression &node) = 0;
    virtual void visit(class LAndExp &node) = 0;
    virtual void visit(class LOrExp &node) = 0;
    virtual void visit(class MulExp &node) = 0;
    virtual void visit(class PrimaryExp &node) = 0;
    virtual void visit(class RelExp &node) = 0;
    virtual void visit(class ReturnStmt &node) = 0;
    virtual void visit(class UnaryExp &node) = 0;
    virtual void visit(class UnaryOp &node) = 0;
    virtual void visit(class IntegerLiteral &node) = 0;
    virtual void visit(class Number &node) = 0;
    virtual void visit(class BoolLiteral &node) = 0;
    virtual void visit(class CharLiteral &node) = 0;
    virtual void visit(class FloatLiteral &node) = 0;
    virtual void visit(class FunctionType &node) = 0;

};


#endif //COMPILER_VISTORAST_H
