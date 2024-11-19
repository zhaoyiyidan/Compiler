//
// Created by 赵鲲翔 on 2024/10/28.
//
#include "Analysis.h"
#include "../Syntax/header/ALLHEADER.h"
#include <limits>
void Analysis::visit(const FunctionDec &node) {
    auto type=node.type->GetNodeType();
    auto name=node.name;
    symbolTable.EnterScope();
    for (auto &parameter: node.parameters) {
        parameter->accept(*this);
    }
    if (!symbolTable.ExistSymbol(name)){
        symbolTable.InsertSymbol(name, type,1);
    }
     node.body->accept(*this);// it is equaivalent to visit(const compoundstmt &node)
} //
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
    symbolTable.ExitScope();
}
//// /   node->accept(*this);  调用vsist方法，调用是那个根据node实际存储的类型
void Analysis::visit(const VarDecl &node) {
    // probelm here
    auto type=node.type->GetNodeType();
    if (node.VarDef){
    
    auto VarDef=dynamic_cast<class VarDef*>(node.VarDef.get());
   if (!symbolTable.ExistSymbol(VarDef->identifier)){
       if (!VarDef->expression){
       symbolTable.InsertSymbol(VarDef->identifier, type,1);
       }
       else{
           auto expression=dynamic_cast<class EXP*>(VarDef->expression.get());
           double value=calculate(*expression);
           symbolTable.InsertSymbol(VarDef->identifier, type,value,1);
       }
   }
   else{
       std::cerr<<"Error: Variable "<<VarDef->identifier<<" has been declared before"<<std::endl;
   }
   
    }
    for (auto &VarDef: node.VarDefs) {
        auto VarDef_=dynamic_cast<class VarDef*>(VarDef.get());
        if (!symbolTable.ExistSymbol(VarDef_->identifier)){
            if (!VarDef_->expression){
            symbolTable.InsertSymbol(VarDef_->identifier, type,1);
            }
            else {
                auto expression=dynamic_cast<class EXP*>(VarDef_->expression.get());
                double value=calculate(*expression);
                symbolTable.InsertSymbol(VarDef_->identifier, type,value,1);
            }
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
        auto expression=dynamic_cast<class EXP*>(VarDef->expression.get());
        double value=calculate(*expression);
        symbolTable.InsertSymbol(VarDef->identifier, type,value,0);
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
void Analysis::visit(const class BreakStmt &node) {}
void Analysis::visit(const class ContinueStmt &node) {}
void Analysis::visit(const class EXP &node) {

}
void Analysis::visit(const StructDecl &node) {
    symbolTable.structFlag=true;
    symbolTable.structName=node.name;
    symbolTable.InsertSymbol(node.name);
    node.body->accept(*this);
    symbolTable.structFlag=false;
    symbolTable.structName="null";
}
void Analysis::visit(const StructBody &node) {
   symbolTable.EnterScope();
   for (auto &stmt: node.body) {
       stmt->accept(*this);
   }
   symbolTable.ExitScope();
}
double Analysis::calculate(const class EXP &node) {
    // probelm here
    auto Left=dynamic_cast<class EXP*>(node.Left.get());
    auto Right=dynamic_cast<class EXP*>(node.Right.get());
    double left_value=0,right_value=0;
    if (Left){
        left_value= calculate(*Left);
    }
    if (Right){
        right_value= calculate(*Right);
    }
    if (left_value==std::numeric_limits<double>::quiet_NaN()||right_value==std::numeric_limits<double>::quiet_NaN()){
        return std::numeric_limits<double>::quiet_NaN();
    }
    if (Left&&Right)
    return applyOp(node.value,left_value,right_value);
        // if it is IDEN
    if (symbolTable.ExistSymbol(node.value)&&node.IDEN){
        return symbolTable.GetSymbol(node.value).second;
    }
    else{
        try{
        return std::stod(node.value);}
        catch (std::exception &e){
            char ch=node.value[1];
            return ch;
        }
    }
}
double Analysis::applyOp(const std::string& op, double a, double b) {
    if (op == "+") return a + b;
    else if (op == "-") return a - b;
    else if (op == "*") return a * b;
    else if (op == "/") return a / b;
    else if (op == "%") return static_cast<int>(a) % static_cast<int>(b);
    else if (op == "&&") return static_cast<bool>(a) && static_cast<bool>(b);
    else if (op == "||") return static_cast<bool>(a) || static_cast<bool>(b);
    else if (op == ">") return a > b;
    else if (op == "<") return a < b;
    else if (op == ">=") return a >= b;
    else if (op == "<=") return a <= b;
    else if (op == "==") return a == b;
    else if (op == "!=") return a != b;
    else if (op == "!") return !static_cast<bool>(a);
    throw std::runtime_error("Unknown operator");

}
void Analysis::visit(const FunctionParameters &node) {
   auto type=node.type->GetNodeType();
    if (!symbolTable.ExistSymbol(node.IDEN)){
         symbolTable.InsertSymbol(node.IDEN, type,1);
    }
    else{
       throw std::runtime_error("Error: Variable "+node.IDEN+" has been declared before");
    }
}
