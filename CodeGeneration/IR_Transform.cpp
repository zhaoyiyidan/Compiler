//
// Created by 赵鲲翔 on 2024/11/20.
//

#include "IR_Transform.h"
void IR_Transform::visit(const class ConstDecl &node){
    node.ConstDef->accept(*this);
    for(auto &constDef : node.ConstDefs){
        constDef->accept(*this);
    }
}
void IR_Transform::visit(const class ConstDef &node) {
    llvm_part.builder.SetInsertPoint(llvm_part.current->block);
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
void IR_Transform::visit(const class Decl &node) {}
void IR_Transform::visit(const class FunctionDec &node){

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
     this->BlockBr(llvm_part.root);

    // set it nullptr
    llvm_part.currentFunction= nullptr;
    llvm_part.current= nullptr;
    llvm_part.root= nullptr;
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
    /*
    if (llvm_part.current->block!=llvm_part.tem)// 两个不一样
        std::runtime_error("1");
    llvm_part.builder.SetInsertPoint(llvm_part.current->block);// here is the problem
     */
    llvm_part.builder.SetInsertPoint(llvm_part.current->child.back()->block);// no current block,but the last block of child
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

        // basic block 有问题
        // auto a=llvm::BasicBlock::Create(llvm_part.context,"2",llvm_part.currentFunction);
        // llvm_part.builder.SetInsertPoint(a);

        llvm::AllocaInst *allocaInst = llvm_part.builder.CreateAlloca(llvm_type, nullptr, node.identifier);
        llvm_part.builder.CreateStore(llvm_value, allocaInst);
    }
}
void IR_Transform::visit(const class AddExp &node)   {}
void IR_Transform::visit(const class AssignStmt &node) {}
void IR_Transform::visit(const class BinaryOperator &node){}
void IR_Transform::visit(const class compoundstmt &node){

   // get the non-const pointer of node
    compoundstmt *node_=const_cast<compoundstmt*>(&node);
    this->CreateNewScope(node_);

    // create a new block, and reset the current
    llvm_part.CreateNewBlock(BodyName);
    auto Whether=INT(0);
    auto temRoot=llvm_part.current;
    for(auto &stmt : node.stmts){
        llvm_part.current=temRoot;
        if (Whether.number==1){
            BodyName="compoundstmt";
            temRoot->condition.push_back(1);
            llvm_part.CreateNewBlock("compoundstmt");
            Whether.number=0;
        }
        if (stmt->GetNodeType()=="compoundstmt"){
            BodyName="compoundstmt";
            temRoot->condition.push_back(1);
            Whether.number=1;
        }
        stmt->accept(*this);
    }
    // this->BlockBr(llvm_part.root);
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
void IR_Transform::visit(const class IFStmt &node) {
    condition= evaluateExpression(node.condition->GetNodeType()).first;
    BodyName="IfStmt";
    node.body->accept(*this);
    BodyName="compoundStmt";
}
void IR_Transform::visit(const class WhileStmt &node) {}
void IR_Transform::visit(const class ForStmt &node) {}
void IR_Transform::visit(const class LValue &node) {}
void IR_Transform::visit(const class BreakStmt &node)   {}
void IR_Transform::visit(const class ContinueStmt &node) {}
void IR_Transform::visit(const class EXP &node){}
void IR_Transform::visit(const class FunctionParameters &node){}
void IR_Transform::visit(const class StructDecl &node) {}
void IR_Transform::visit(const class StructBody &node){}



void IR_Transform::CreateNewScope(ASTnode *node){
    // auto sym=symbolTable;
    analysis(node,symbolTable);
    pos++;
    // symbolTable=sym;
}
void IR_Transform::ExitScope(){
    symbolTable.ExitScope();
    pos--;
}
double IR_Transform::CalculateCondition( const class EXP &node){
   // get the non-const pointer of node
    EXP *node_=const_cast<EXP*>(&node);
    return evaluateExpression(node_->GetNodeType()).first;
}


// given a block tree, we need to do br for each branch， it will creat Br for whole tree
void IR_Transform::BlockBr(std::shared_ptr<BlockTree> tree){
    if (tree->child.empty()){
        return;
    }

    int a=0;
    int b=1;
    int Br[tree->child.size()];// to distinguish whether the branch is done
    for(auto &i:Br){
        i=0;
    }
    while (b<tree->child.size()){
        if (tree->condition[b-1]==0){
            continue;
        }

        if (Br[a]==0){
        BlockBr(tree->child[a]);
        Br[a]=1;
        }
        if (Br[b]==0){
        BlockBr(tree->child[b]);
        Br[b]=1;
        }
        if(CombineTwoBranch(tree,tree->child[a],tree->child[b],b)){
            a++;
            b++;
        }
        else{
            b++;
        }
    }
}
bool IR_Transform::CombineTwoBranch(std::shared_ptr<BlockTree > ParaentTree,std::shared_ptr<BlockTree> LeftTree,std::shared_ptr<BlockTree> RightTree,int position){

    if (position>ParaentTree->condition.size() || ParaentTree->condition[position-1]==0){
        return false;
    }
    llvm::BasicBlock *left;
    llvm::BasicBlock *right;
    if (LeftTree->child.empty()){
        left=LeftTree->block;
    }
    else{
        left=LeftTree->FindRightMostLeaf(LeftTree)->block;
    }
    // same as above
    if (RightTree->child.empty()){
        right=RightTree->block;
    }
    else{
        right=RightTree->FindLeftMostLeaf(RightTree)->block;
    }
    llvm_part.builder.SetInsertPoint(left);
    llvm_part.builder.CreateBr(right);
    return true;
}

