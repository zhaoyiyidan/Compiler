//
// Created by 赵鲲翔 on 2024/11/20.
//

#include "IR_Transform.h"
void visit(const class ConstDecl &node){}
void visit(const class ConstDef &node) {}
void visit(const class Decl &node) {}
void IR_Transform::visit(const class FunctionDec &node){

    // lvm::Function *func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, node.name, &llvm_part.module);
    // llvm::BasicBlock *entry = llvm::BasicBlock::Create(llvm_part.context, "entry", func);
    // llvm_part.builder.SetInsertPoint(entry);
    // llvm::Function::arg_iterator argsValues = func->arg_begin();

    //when you create a new function, you need to create a new symbol table and when you finish the function, you need to delete the symbol table
    this->CreateNewSymbolTable(node.body.get());

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
    // delete the symbol table
    this->DeleteSymbolTable();
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
    if (!symbolTableVector.empty()&&symbolTableVector.back().ExistSymbol(node.identifier)){
        Symbol& symbol=symbolTableVector.back().GetTheSymbol(node.identifier);
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
void visit(const class AddExp &node)   {}
void visit(const class AssignStmt &node) {}
void visit(const class BinaryOperator &node){}
void IR_Transform::visit(const class compoundstmt &node){
    // if we only have basic block in the function
    this->CreateBasicBlock("CompoundStmt");

    for(auto &stmt : node.stmts){
        stmt->accept(*this);
    }
    // there is something we need to do here
}
void visit(const class EqExp &node) {}
void visit(const class Expression &node) {}
void visit(const class LAndExp &node) {}
void visit(const class LOrExp &node) {}
void visit(const class MulExp &node) {}
void visit(const class PrimaryExp &node) {}
void visit(const class RelExp &node) {}
void visit(const class ReturnStmt &node) {}
void visit(const class UnaryExp &node) {}
void visit(const class UnaryOp &node) {}
void visit(const class IntegerLiteral &node) {}
void visit(const class Number &node) {}
void visit(const class BoolLiteral &node) {}
void visit(const class CharLiteral &node) {}
void visit(const class FloatLiteral &node) {}
void visit(const class FunctionType &node)     {}
void visit(const class IFStmt &node) {}
void visit(const class WhileStmt &node) {}
void visit(const class ForStmt &node) {}
void visit(const class LValue &node) {}
void visit(const class BreakStmt &node)   {}
void visit(const class ContinueStmt &node) {}
void visit(const class EXP &node){}
void visit(const class FunctionParameters &node){}
void visit(const class StructDecl &node) {}
void visit(const class StructBody &node){}
// it is used to create a new basic block
void IR_Transform::CreateBasicBlock(const std::string &name){
    llvm_part.CreateNewBlock(name);
}
void IR_Transform::CreateNewSymbolTable(ASTnode *node){
    symbolTableVector.push_back(analysis(node));
}
void IR_Transform::DeleteSymbolTable(){
    symbolTableVector.pop_back();
}
