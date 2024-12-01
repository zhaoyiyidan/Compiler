//
// Created by 赵鲲翔 on 2024/11/20.
//

#include "IR_Transform.h"
void IR_Transform::visit(const class ConstDecl &node){}
void IR_Transform::visit(const class ConstDef &node) {}
void IR_Transform::visit(const class Decl &node) {}
void IR_Transform::visit(const class FunctionDec &node){

    // lvm::Function *func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, node.name, &llvm_part.module);
    // llvm::BasicBlock *entry = llvm::BasicBlock::Create(llvm_part.context, "entry", func);
    // llvm_part.builder.SetInsertPoint(entry);
    // llvm::Function::arg_iterator argsValues = func->arg_begin();

    std::vector<llvm::Type*> paramTypes;
    // create the parameters of the function
    for(auto &arg : node.parameters){
        if (!arg){
            continue;
        }
        auto pair=std::make_pair(arg->GetNodeType(),"," );
        std::string type=pair.first;
        std::string name=pair.second;
        llvm::Type *llvm_type;
        // depending on the type of the function
        if (type=="int"){
            llvm_type=llvm::Type::getInt32Ty(llvm_part.context);
        }
        else if (type=="void"){
            llvm_type=llvm::Type::getVoidTy(llvm_part.context);
        }
        else if (type=="float"){
            llvm_type=llvm::Type::getFloatTy(llvm_part.context);
        }
        else if (type=="double"){
            llvm_type=llvm::Type::getDoubleTy(llvm_part.context);
        }
        else if (type=="char"){
            llvm_type=llvm::Type::getInt8Ty(llvm_part.context);
        }
        else if (type=="bool"){
            llvm_type=llvm::Type::getInt1Ty(llvm_part.context);
        }
        paramTypes.push_back(llvm_type);
    }
    llvm::FunctionType *funcType;
    // depending on the type of the function, we need to create the function with the correct type
    std::string type=node.type->GetNodeType();
    if (type=="int"){
        funcType = llvm::FunctionType::get(llvm::Type::getInt32Ty(llvm_part.context), paramTypes,false);
    }
    else if (type=="void"){
        funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm_part.context), paramTypes,false);
    }
    else if (type=="float"){
        funcType = llvm::FunctionType::get(llvm::Type::getFloatTy(llvm_part.context), paramTypes,false);
    }
    else if (type=="double"){
        funcType = llvm::FunctionType::get(llvm::Type::getDoubleTy(llvm_part.context), paramTypes,false);
    }
    else if (type=="char"){
        funcType = llvm::FunctionType::get(llvm::Type::getInt8Ty(llvm_part.context), paramTypes,false);
    }
    else if (type=="bool"){
        funcType = llvm::FunctionType::get(llvm::Type::getInt1Ty(llvm_part.context), paramTypes,false);
    }
    llvm_part.currentFunction = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, node.name, &llvm_part.module);
    node.body->accept(*this);

    // set it nullptr
    llvm_part.currentFunction= nullptr;
    // delete the last symbol table
}
void IR_Transform::visit(const class VarDecl &node) {
    node.VarDef->accept(*this);
    for(auto &varDef : node.VarDefs){
        varDef->accept(*this);
    }
}
void IR_Transform::visit(const class VarDef &node) {
    // handle the case no global variable
    llvm_part.builder.SetInsertPoint(llvm_part.blockStack.back());
    if (!symbolTable.scopeStack.empty()&&symbolTable.ExistSymbol(node.identifier)){
        Symbol& symbol=symbolTable.GetTheSymbol(node.identifier);
        double value=symbol.value;
        // construct the type of the variable
        llvm::Type *llvm_type;
        llvm::Value *llvm_value;
        if (symbol.type=="int"){
            llvm_type=llvm::Type::getInt32Ty(llvm_part.context);
            llvm_value=llvm::ConstantInt::get(llvm_type, value);
        }
        else if (symbol.type=="void"){
            llvm_type=llvm::Type::getVoidTy(llvm_part.context);
        }
        else if (symbol.type=="float"){
            llvm_type=llvm::Type::getFloatTy(llvm_part.context);
            llvm_value=llvm::ConstantFP::get(llvm_type, value);
        }
        else if (symbol.type=="double"){
            llvm_type=llvm::Type::getDoubleTy(llvm_part.context);
            llvm_value=llvm::ConstantFP::get(llvm_type, value);
        }
        else if (symbol.type=="char"){
            llvm_type=llvm::Type::getInt8Ty(llvm_part.context);
            llvm_value=llvm::ConstantInt::get(llvm_type, value);
        }
        else if (symbol.type=="bool"){
            llvm_type=llvm::Type::getInt1Ty(llvm_part.context);
        }
        // create the variable
        llvm::AllocaInst *allocaInst = llvm_part.builder.CreateAlloca(llvm_type, nullptr, node.identifier);
        llvm_part.builder.CreateStore(llvm_value, allocaInst);

    }
}
void IR_Transform::visit(const class AddExp &node)   {}
void IR_Transform::visit(const class AssignStmt &node) {}
void IR_Transform::visit(const class BinaryOperator &node){}
void IR_Transform::visit(const class compoundstmt &node){
    // if we only have basic block in the function
    // this->CreateBasicBlock("compoundStmt");
//
   // get the non-const pointer of node
    compoundstmt *node_=const_cast<compoundstmt*>(&node);
    this->CreateNewScope(node_);
    // if we have mutiple scope in the function
    this->CreateBasicBlock("compoundStmt");
    if (llvm_part.blockStack.size()>1){
        if (llvm_part.blockStack[llvm_part.blockStack.size()-2]->getName().str()=="compoundStmt"){
            llvm_part.builder.SetInsertPoint(llvm_part.blockStack[llvm_part.blockStack.size()-2]);
            llvm_part.builder.CreateBr(llvm_part.blockStack.back());
        }
    }
    for(auto &stmt : node.stmts){
        // this->CreateNewSymbolTable(stmt.get());
        stmt->accept(*this);
        // this->DeleteSymbolTable();
    }
    // there is something we need to do here
    this->ExitScope();
}
void IR_Transform::visit(const class EqExp &node) {}
void IR_Transform::visit(const class Expression &node) {}
void IR_Transform::visit(const class LAndExp &node) {}
void IR_Transform::visit(const class LOrExp &node) {}
void IR_Transform::visit(const class MulExp &node) {}
void IR_Transform::visit(const class PrimaryExp &node) {}
void IR_Transform::visit(const class RelExp &node) {}
void IR_Transform::visit(const class ReturnStmt &node) {}
void IR_Transform::visit(const class UnaryExp &node) {}
void IR_Transform::visit(const class UnaryOp &node) {}
void IR_Transform::visit(const class IntegerLiteral &node) {}
void IR_Transform::visit(const class Number &node) {}
void IR_Transform::visit(const class BoolLiteral &node) {}
void IR_Transform::visit(const class CharLiteral &node) {}
void IR_Transform::visit(const class FloatLiteral &node) {}
void IR_Transform::visit(const class FunctionType &node)     {}
void IR_Transform::visit(const class IFStmt &node) {}
void IR_Transform::visit(const class WhileStmt &node) {}
void IR_Transform::visit(const class ForStmt &node) {}
void IR_Transform::visit(const class LValue &node) {}
void IR_Transform::visit(const class BreakStmt &node)   {}
void IR_Transform::visit(const class ContinueStmt &node) {}
void IR_Transform::visit(const class EXP &node){}
void IR_Transform::visit(const class FunctionParameters &node){}
void IR_Transform::visit(const class StructDecl &node) {}
void IR_Transform::visit(const class StructBody &node){}
// it is used to create a new basic block
void IR_Transform::CreateBasicBlock(const std::string &name){
    llvm_part.CreateNewBlock(name);
}


void IR_Transform::CreateNewScope(ASTnode *node){
    // auto sym=symbolTable;
    analysis(node,symbolTable);
    // symbolTable=sym;
}
void IR_Transform::ExitScope(){
    symbolTable.ExitScope();
}
