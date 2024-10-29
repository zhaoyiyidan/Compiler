//
// Created by 赵鲲翔 on 2024/10/28.
//
#include "Analysis.h"
#include "../Syntax/header/ALLHEADER.h"
void Analysis::visit(const FunctionDec &node) {
    node.body->accept(*this);
}
void Analysis::visit(const compoundstmt &node) {
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