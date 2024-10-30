//
// Created by 赵鲲翔 on 2024/10/28.
//
#include "Analysis.h"
#include "../Syntax/header/ALLHEADER.h"
void Analysis::visit(const FunctionDec &node) {
    node.body->accept(*this);
}
void Analysis::visit(const compoundstmt &node) {
    symbolTable.EnterScope();
    for (auto &stmt: node.stmts) {
       if (stmt->GetNodeType()=="compoundstmt"){
        symbolTable.EnterScope();
        stmt->accept(*this);
        symbolTable.ExitScope();
       }
       else{
              stmt->accept(*this);
       }
    }
}
void Analysis::visit(const VarDecl &node) {
    auto type=node.type->GetNodeType();
    auto VarDef=dynamic_cast<class VarDef*>(node.VarDef.get());
   if (!symbolTable.ExistSymbol(VarDef->identifier)){
       symbolTable.InsertSymbol(VarDef->identifier, type,1);
   }
   else{
       std::cerr<<"Error: Variable "<<VarDef->identifier<<" has been declared before"<<std::endl;
   }
    for (auto &VarDef: node.VarDefs) {
        auto VarDef_=dynamic_cast<class VarDef*>(VarDef.get());
        if (!symbolTable.ExistSymbol(VarDef_->identifier)){
            symbolTable.InsertSymbol(VarDef_->identifier, type,1);
        }
        else{
            std::cerr<<"Error: Variable "<<VarDef_->identifier<<" has been declared before"<<std::endl;
        }
    }

}
void Analysis::visit(const ConstDecl &node) {
    auto type=node.type->GetNodeType();
    auto VarDef=dynamic_cast<class ConstDef*>(node.ConstDef.get());
    if (!symbolTable.ExistSymbol(VarDef->identifier)){
        symbolTable.InsertSymbol(VarDef->identifier, type,0);
    }
    else{
        std::cerr<<"Error: Variable "<<VarDef->identifier<<" has been declared before"<<std::endl;
    }
    for (auto &VarDef: node.ConstDefs) {
        auto VarDef_=dynamic_cast<class ConstDef*>(VarDef.get());
        if (!symbolTable.ExistSymbol(VarDef_->identifier)){
            symbolTable.InsertSymbol(VarDef_->identifier, type,0);
        }
        else{
            std::cerr<<"Error: Variable "<<VarDef_->identifier<<" has been declared before"<<std::endl;
        }
    }
}
void Analysis::visit(const AssignStmt &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const Expression &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const PrimaryExp &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const ReturnStmt &node) {
    // Implementation
    int a;
}

void Analysis::visit(const BoolLiteral &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const CharLiteral &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const FloatLiteral &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const FunctionType &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const BinaryOperator &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const IntegerLiteral &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const Decl &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const EqExp &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const AddExp &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const LOrExp &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const MulExp &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const Number &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const RelExp &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const VarDef &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const LAndExp &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const UnaryOp &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const ConstDef &node) {
    // Implementation
    int a=1;
}

void Analysis::visit(const UnaryExp &node) {
    // Implementation
    int a=1;
}
void Analysis::visit(const class IFStmt &node) {

}
void Analysis::visit(const class WhileStmt &node) {}
void Analysis::visit(const class ForStmt &node) {}
void Analysis::visit(const class LValue &node) {}