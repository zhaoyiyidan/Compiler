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
    //
    symbolTable=analysis(node.body.get());
    std::vector<llvm::Type*> paramTypes;
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
    llvm_part.currentFunction= nullptr;
}
void IR_Transform::visit(const class VarDecl &node) {
    node.VarDef->accept(*this);
    for(auto &varDef : node.VarDefs){
        varDef->accept(*this);
    }
}
void IR_Transform::visit(const class VarDef &node) {
    if (ExistSymbolTable&&symbolTable.ExistSymbol(node.identifier)){
        auto symbol=symbolTable.GetTheSymbol(node.identifier);
        // construct the type of the variable
        llvm::Type *llvm_type;
        if (symbol.type=="int"){
            llvm_type=llvm::Type::getInt32Ty(llvm_part.context);
        }
        else if (symbol.type=="void"){
            llvm_type=llvm::Type::getVoidTy(llvm_part.context);
        }
        else if (symbol.type=="float"){
            llvm_type=llvm::Type::getFloatTy(llvm_part.context);
        }
        else if (symbol.type=="double"){
            llvm_type=llvm::Type::getDoubleTy(llvm_part.context);
        }
        else if (symbol.type=="char"){
            llvm_type=llvm::Type::getInt8Ty(llvm_part.context);
        }
        else if (symbol.type=="bool"){
            llvm_type=llvm::Type::getInt1Ty(llvm_part.context);
        }
        // create the variable
        llvm::AllocaInst *allocaInst = llvm_part.builder.CreateAlloca(llvm_type, nullptr, node.identifier);
        
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
void IR_Transform::CreateBasicBlock(const std::string &name){
    llvm_part.CreateNewBlock(name);
}
