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
    // now it is same as VarDef
    llvm_part.builder.SetInsertPoint(llvm_part.current->child.back()->block);
    if (!analysis1.symbolTable.scopeStack.empty()&&analysis1.symbolTable.ExistSymbol(node.identifier)){
        Symbol& symbol=analysis1.symbolTable.GetTheSymbol(node.identifier);
        // construct the type of the variable
        llvm::Type *llvm_type;
        llvm::Value *llvm_value;
        // 计算前，先规定type
        TypeUsedTem=symbol.type;
        node.expression->accept(*this);// calculate the llvm value of the variable
        llvm_value=returnValue;
        if (symbol.type=="int"){
            llvm_type=llvm::Type::getInt32Ty(llvm_part.context);
            // llvm_value=llvm::ConstantInt::get(llvm_type, value);
        }
        else if (symbol.type=="void"){
            llvm_type=llvm::Type::getVoidTy(llvm_part.context);
        }
        else if (symbol.type=="float"){
            llvm_type=llvm::Type::getFloatTy(llvm_part.context);
            // llvm_value=llvm::ConstantFP::get(llvm_type, value);
        }
        else if (symbol.type=="double"){
            llvm_type=llvm::Type::getDoubleTy(llvm_part.context);
            // llvm_value=llvm::ConstantFP::get(llvm_type, value);
        }
        else if (symbol.type=="char"){
            llvm_type=llvm::Type::getInt8Ty(llvm_part.context);
            // llvm_value=llvm::ConstantInt::get(llvm_type, value);
        }
        else if (symbol.type=="bool"){
            // llvm_type=llvm::Type::getInt1Ty(llvm_part.context);
        }

        llvm::AllocaInst *allocaInst = llvm_part.builder.CreateAlloca(llvm_type, nullptr, node.identifier);
        llvm::Type* valueType = llvm_value->getType();
        llvm::Type* allocaType = allocaInst->getAllocatedType();
        // 错误检查
        if (llvm_value == nullptr) {
            throw std::runtime_error("llvm_value is a null pointer.");
        }
        if (allocaInst == nullptr) {
            throw std::runtime_error("allocaInst is a null pointer.");
        }
        if (valueType != allocaType) {
            throw std::runtime_error("Type mismatch: llvm_value type does not match allocaInst type.");
        }

        llvm_part.builder.CreateStore(llvm_value, allocaInst);
        // set the allocaInst of the symbol
        symbol.allocaInst=allocaInst;
        symbol.llvmValue=llvm_value;
    }
}
void IR_Transform::visit(const class Decl &node) {}
void IR_Transform::visit(const class FunctionDec &node){

    std::vector<llvm::Type*> paramTypes;
    // create the parameters of the function
    std::vector<std::string> parametersTodelet;
    for(auto &arg : node.parameters){
        if (!arg){
            continue;
        }
        auto pair=(arg->GetNodeType());
        int position_=pair.find(",");
        std::string type=pair.substr(0,position_);
        std::string name=pair.substr(position_+1,pair.size()-1);
        parametersTodelet.push_back(name);
        // insert the parameter into the symbol table
        analysis1.symbolTable.InsertSymbol(name, type,666);
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
        paramTypes.push_back(llvm_type);// 没有正确声明
    }
    llvm::FunctionType *funcType;
    // depending on the type of the function, we need to create the function with the correct type
    std::string type=node.type->GetNodeType();
    //
    TypeForReturn=type;
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
    // 参数命名
    int i=0;
    for (auto &arg : llvm_part.currentFunction->args()) {
        arg.setName(parametersTodelet[i]);
        i++;
    }
    node.body->accept(*this);
    this->BlockBr(llvm_part.root);

    // set it nullptr
    for (auto &parameter:parametersTodelet){
        analysis1.symbolTable.deleteSymbol(parameter);
    }
    llvm_part.currentFunction= nullptr;
    llvm_part.current= nullptr;
    llvm_part.root= nullptr;
    // delete the last symbol table
}
void IR_Transform::visit(const class VarDecl &node) {
    if (node.VarDef)
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
    if (!analysis1.symbolTable.scopeStack.empty()&&analysis1.symbolTable.ExistSymbol(node.identifier)){
        Symbol& symbol=analysis1.symbolTable.GetTheSymbol(node.identifier);
        // construct the type of the variable
        llvm::Type *llvm_type;
        llvm::Value *llvm_value;
        //
        TypeUsedTem=symbol.type;
        if (node.expression){
        node.expression->accept(*this);// calculate the llvm value of the variable
        llvm_value=returnValue;
        }
        else{
        llvm_value= nullptr;
        }
        if (symbol.type=="int"){
            llvm_type=llvm::Type::getInt32Ty(llvm_part.context);
            //llvm_value=llvm::ConstantInt::get(llvm_type, value);
        }
        else if (symbol.type=="void"){
            llvm_type=llvm::Type::getVoidTy(llvm_part.context);
        }
        else if (symbol.type=="float"){
            llvm_type=llvm::Type::getFloatTy(llvm_part.context);
            // llvm_value=llvm::ConstantFP::get(llvm_type, value);
        }
        else if (symbol.type=="double"){
            llvm_type=llvm::Type::getDoubleTy(llvm_part.context);
            // llvm_value=llvm::ConstantFP::get(llvm_type, value);
        }
        else if (symbol.type=="char"){
            llvm_type=llvm::Type::getInt8Ty(llvm_part.context);
            // llvm_value=llvm::ConstantInt::get(llvm_type, value);
        }
        else if (symbol.type=="bool"){
            llvm_type=llvm::Type::getInt1Ty(llvm_part.context);
        }
        llvm::AllocaInst *allocaInst = llvm_part.builder.CreateAlloca(llvm_type, nullptr, node.identifier);

        if (llvm_value){
        llvm_part.builder.CreateStore(llvm_value, allocaInst);
        }
        // set the allocaInst of the symbol
        symbol.allocaInst=allocaInst;
        symbol.llvmValue=llvm_value;
    }
    else {
        throw std::runtime_error("Symbol not found");
    }
}
void IR_Transform::visit(const class AddExp &node)   {}
void IR_Transform::visit(const class AssignStmt &node) {
    llvm_part.builder.SetInsertPoint(llvm_part.current->child.back()->block);
    if (!analysis1.symbolTable.scopeStack.empty()&&analysis1.symbolTable.ExistSymbol(node.identifier)){
        Symbol& symbol=analysis1.symbolTable.GetTheSymbol(node.identifier);
        llvm::Value *llvm_value;
        TypeUsedTem=symbol.type;
        node.expression->accept(*this);
        llvm_value=returnValue;
        if (symbol.allocaInst){
        llvm_part.builder.CreateStore(llvm_value, symbol.allocaInst);
        }
        else{
            throw std::runtime_error("Symbol not found");
        }
    }
    else {
        throw std::runtime_error("Symbol not found");
    }
}
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
        // when get out ,create a new compoundstmt
        // 如果if 出去 马上就是一个while 或者for 错误
        if (Whether.number==1){
            std::string type=stmt->GetNodeType();
            if (type=="ForStmt"||type=="WhileStmt"||type=="IFStmt"){
                temRoot->condition.push_back(1);
            }
            else{
            temRoot->condition.push_back(1);
            llvm_part.CreateNewBlock("compoundstmt");
            temRoot=llvm_part.current;// 更新temRoot
            Whether.number=0;
            }
        }
        // for {}
        if (stmt->GetNodeType()=="compoundstmt"&&BodyName=="compoundstmt"){
            temRoot->condition.push_back(1);
            Whether.number=1;
        }
        // for if,for,while stmt
        if (stmt->GetNodeType()=="ForStmt"||stmt->GetNodeType()=="WhileStmt"||stmt->GetNodeType()=="IFStmt"){
            Whether.number=1;
            temRoot->condition.push_back(1);
        }
        stmt->accept(*this);
    }
    llvm_part.current=temRoot;
    this->ExitScope();
}
void IR_Transform::visit(const class EqExp &node) {}
void IR_Transform::visit(const class Expression &node) {}
void IR_Transform::visit(const class LAndExp &node) {}
void IR_Transform::visit(const class LOrExp &node) {}
void IR_Transform::visit(const class MulExp &node) {}
void IR_Transform::visit(const class PrimaryExp &node) {}
void IR_Transform::visit(const class RelExp &node) {}
void IR_Transform::visit(const class ReturnStmt &node) {
    llvm_part.builder.SetInsertPoint(llvm_part.current->child.back()->block);
    if (node.Expression){
        TypeUsedTem=TypeForReturn;
        node.Expression->accept(*this);
        llvm_part.builder.CreateRet(returnValue);
    }
    else{
        llvm_part.builder.CreateRetVoid();
    }
}
void IR_Transform::visit(const class UnaryExp &node) {}
void IR_Transform::visit(const class UnaryOp &node) {}
void IR_Transform::visit(const class IntegerLiteral &node) {}
void IR_Transform::visit(const class Number &node) {}
void IR_Transform::visit(const class BoolLiteral &node) {}
void IR_Transform::visit(const class CharLiteral &node) {}
void IR_Transform::visit(const class FloatLiteral &node) {}
void IR_Transform::visit(const class FunctionType &node)     {}
void IR_Transform::visit(const class IFStmt &node) {
    llvm_part.CreateNewBlockWi("IFStmt");
    // create entry block
    llvm::BasicBlock* entry=llvm::BasicBlock::Create(llvm_part.context,"entry",llvm_part.currentFunction);
    auto entrytree=std::make_shared<BlockTree>("entry",entry);
    llvm_part.current->SetTree(entrytree);
    auto a=llvm_part.current;
    BodyName="IFStmtBody";
    node.body->accept(*this);
    BodyName="compoundstmt";
    auto Leftbody=llvm_part.current->FindLeftMostLeaf(llvm_part.current)->block;
    auto RightBody=llvm_part.current->FindRightMostLeaf(llvm_part.current)->block;
    // else if body exist ?
    llvm::BasicBlock* Leftelsebody=nullptr;
    llvm::BasicBlock* Rightelsebody=nullptr;
    if (node.else_body){
        llvm_part.current=a;
        BodyName="IFStmtElseBody";
        node.else_body->accept(*this);
        BodyName="compoundstmt";
        Leftelsebody=llvm_part.current->FindLeftMostLeaf(llvm_part.current)->block;
        Rightelsebody=llvm_part.current->FindRightMostLeaf(llvm_part.current)->block;
    }
    // create the exit block
    auto exit=llvm::BasicBlock::Create(llvm_part.context,"exit",llvm_part.currentFunction);
    auto exittree=std::make_shared<BlockTree>("exit",exit);
    a->SetTree(exittree);
    // create Condbr
    llvm_part.builder.SetInsertPoint(entry);
    node.condition->accept(*this);
    if (node.else_body)
    {
        llvm_part.builder.SetInsertPoint(entry);
        llvm_part.builder.CreateCondBr(returnValue,Leftbody,Leftelsebody);
    // create br
    llvm_part.builder.SetInsertPoint(RightBody);
    llvm_part.builder.CreateBr(exit);
    llvm_part.builder.SetInsertPoint(Rightelsebody);
    llvm_part.builder.CreateBr(exit);
    }
    else {
        llvm_part.builder.CreateCondBr(returnValue,Leftbody,exit);
        llvm_part.builder.SetInsertPoint(RightBody);
        llvm_part.builder.CreateBr(exit);
    }
}
void IR_Transform::visit(const class WhileStmt &node) {
    llvm_part.CreateNewBlockWi("WhileStmt");
    // do a dynamic cast to get EXP node
    auto EXPNode=dynamic_cast<EXP*>(node.condition.get());
    auto IDEN=EXPNode->Left->GetNodeType();
    // get the symbol of the variable
    auto symbol=analysis1.symbolTable.GetTheSymbol(IDEN);
    // create a loop condition block
    llvm::BasicBlock* loopCond=llvm::BasicBlock::Create(llvm_part.context,"loopCond",llvm_part.currentFunction);
    auto loopCondTree=std::make_shared<BlockTree>("loopCond",loopCond);
    llvm_part.current->SetTree(loopCondTree);
    auto a=llvm_part.current;
    // create the body block
    BodyName="WhileStmtBody";
    node.body->accept(*this);
    BodyName="compoundstmt";
    // find the left most leaf and right most leaf in body
    auto LeftLeaves=llvm_part.current->FindLeftMostLeaf(llvm_part.current);
    auto RightLeaves=llvm_part.current->FindRightMostLeaf(llvm_part.current);
    // create the exit block
    auto exit=llvm::BasicBlock::Create(llvm_part.context,"exit",llvm_part.currentFunction);
    auto exitTree=std::make_shared<BlockTree>("exit",exit);
    a->SetTree(exitTree);
    // create condbr
    llvm_part.builder.SetInsertPoint(loopCond);
    node.condition->accept(*this);
    llvm_part.builder.CreateCondBr(returnValue,LeftLeaves->block,exit);
    // create br
    llvm_part.builder.SetInsertPoint(RightLeaves->block);
    llvm_part.builder.CreateBr(loopCond);

}
void IR_Transform::visit(const class ForStmt &node) {
    // creat a blovk
    llvm_part.CreateNewBlockWi("ForStmt");
   // create entry block
    llvm::BasicBlock* entry=llvm::BasicBlock::Create(llvm_part.context,"entry",llvm_part.currentFunction);
    auto entrytree=std::make_shared<BlockTree>("entry",entry);
    llvm_part.current->SetTree(entrytree);
    // intilaize i
    auto initialzie=dynamic_cast<VarDecl*>(node.init.get());
    TheAnalysis(initialzie,analysis1);
    auto b=dynamic_cast<VarDef*>(initialzie->VarDef.get());
    std::string i=b->identifier;
    node.init->accept(*this);
    // create the loop block
    llvm::BasicBlock* brcond=llvm::BasicBlock::Create(llvm_part.context,"loop",llvm_part.currentFunction);
    auto brcondtree=std::make_shared<BlockTree>("loop",brcond);
    llvm_part.current->SetTree(brcondtree);
    // create br in entry block
    llvm_part.builder.SetInsertPoint(entry);
    llvm_part.builder.CreateBr(brcond);
    auto a=llvm_part.current;
    // create the body part
    BodyName="ForStmtBody";
    node.body->accept(*this);
    BodyName="compoundstmt";
    // find the left most leaf and right most leaf
    auto LeftLeaves=llvm_part.current->FindLeftMostLeaf(llvm_part.current);
    auto RightLeaves=llvm_part.current->FindRightMostLeaf(llvm_part.current);
    // increase i in right most leaf
    auto rightLeaf1=llvm_part.current->FindRightMostLeaf1(llvm_part.current);
    llvm_part.current=rightLeaf1;
    node.increment->accept(*this);
    // create br in right most leaf
    llvm_part.builder.SetInsertPoint(RightLeaves->block);
    llvm_part.builder.CreateBr(brcond);
    // create the exit block
    auto exit=llvm::BasicBlock::Create(llvm_part.context,"exit",llvm_part.currentFunction);
    auto exittree=std::make_shared<BlockTree>("exit",exit);
    a->SetTree(exittree);
    // create condbr in left most leaf
    llvm_part.builder.SetInsertPoint(brcond);
    node.condition->accept(*this);
    llvm_part.builder.CreateCondBr(returnValue,LeftLeaves->block,exit);
    // delet i
    analysis1.symbolTable.deleteSymbol(i);
}
void IR_Transform::visit(const class LValue &node) {}
void IR_Transform::visit(const class BreakStmt &node)   {}
void IR_Transform::visit(const class ContinueStmt &node) {}
void IR_Transform::visit(const class EXP &node){
    condition=analysis1.calculate(node);
    returnValue=calculateEXP(node,TypeUsedTem);
}
void IR_Transform::visit(const class FunctionParameters &node){}
void IR_Transform::visit(const class StructDecl &node) {}
void IR_Transform::visit(const class StructBody &node){}

void IR_Transform::CreateNewScope(ASTnode *node){
    TheAnalysis(node,analysis1);
    pos++;
}
void IR_Transform::ExitScope(){
    analysis1.symbolTable.ExitScope();
    pos--;
}
// given a block tree, we need to do br for each branch， it will creat Br for whole tree
void IR_Transform::BlockBr(std::shared_ptr<BlockTree> tree){
    if (tree->child.empty()){
        return;
    }
    if (tree->name=="ForStmt"||tree->name=="WhileStmt"||tree->name=="IFStmt"){
        // do block for the child
        for (auto &i:tree->child){
            BlockBr(i);
        }
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
            b++;
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
            if (CombineTwoBranch(tree, tree->child[a], tree->child[b], b)) {
                a++;
                b++;
            } else {
                b++;
            }
    }
}
bool IR_Transform::CombineTwoBranch(std::shared_ptr<BlockTree > &ParaentTree,std::shared_ptr<BlockTree> &LeftTree,std::shared_ptr<BlockTree> &RightTree,int position){
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
bool IR_Transform::CombineTwoBranch(std::shared_ptr<BlockTree> &LeftTree,std::shared_ptr<BlockTree> &RightTree,bool condition){
    if (condition==0){
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

llvm::Value* IR_Transform::ApplyOp(const std::string& op, llvm::Value* a, llvm::Value* b) {
    if (op == "!") return llvm_part.builder.CreateNot(a, "not");
    else if (!b) return nullptr;
    else if (op == "+") return llvm_part.builder.CreateAdd(a,b,"sum");
    else if (op == "-") return llvm_part.builder.CreateSub(a, b, "sub");
    else if (op == "*") return llvm_part.builder.CreateMul(a, b, "mul");
    else if (op == "/") return llvm_part.builder.CreateSDiv(a, b, "div");
    else if (op == "%") return llvm_part.builder.CreateSRem(a, b, "mod");
    else if (op == "&&") return llvm_part.builder.CreateAnd(a,b,"bool");
    else if (op == "||") return llvm_part.builder.CreateOr(a,b,"bool");
    else if (op == ">") return llvm_part.builder.CreateICmpSGT(a, b, "gt");
    else if (op == "<") return llvm_part.builder.CreateICmpSLT(a, b, "lt");
    else if (op == ">=") return llvm_part.builder.CreateICmpSGE(a, b, "ge");
    else if (op == "<=") return llvm_part.builder.CreateICmpSLE(a, b, "le");
    else if (op == "==") return llvm_part.builder.CreateICmpEQ(a, b, "eq");
    else if (op == "!=") return llvm_part.builder.CreateICmpNE(a, b, "ne");

    throw std::runtime_error("Unknown operator");
}

std::string IR_Transform::getTypeString(llvm::Type *type) {
    if (type->isIntegerTy()) {
        unsigned bitWidth = type->getIntegerBitWidth();
        if (bitWidth == 8) {
            return "char";  // 8位整数表示 char
        } else {
            return "int";
        }
    } else if (type->isFloatTy()) {
        return "float";
    } else if (type->isDoubleTy()) {
        return "double";
    } else if (type->isPointerTy()) {
        return nullptr;
    } else if (type->isVoidTy()) {
        return "void";
    } else if (type->isFunctionTy()) {
        return "function";
    } else if (type->isArrayTy()) {
        return "array of " + getTypeString(type->getArrayElementType());
    } else if (type->isStructTy()) {
        return "struct";
    } else {
        return "unknown type";
    }
}
llvm::Value* IR_Transform::calculateEXP(const class EXP &node,std::string type){
    auto Left=dynamic_cast<class EXP*>(node.Left.get());
    auto Right=dynamic_cast<class EXP*>(node.Right.get());
    llvm::Value* left_value= nullptr;
    llvm::Value* right_value= nullptr;
    if (Left){
        left_value= calculateEXP(*Left,type);
    }
    if (Right){
        right_value= calculateEXP(*Right,type);
    }
    if (Left)
        return ApplyOp(node.value,left_value,right_value);

    if (analysis1.symbolTable.ExistSymbol(node.value)&&node.IDEN){
        auto value= analysis1.symbolTable.GetSymbol(node.value).second;
        if (std::isnan(value)){// it uses function parameters
            // return std::numeric_limits<double>::quiet_NaN();
            for (auto &arg:llvm_part.currentFunction->args()){
                if (arg.getName().str()==node.value){
                    return &arg;
                }
            }
        }
        else {
            // 从内存中加载IDEN的值
            auto IDEN=analysis1.symbolTable.GetTheSymbol(node.value);
            auto address=IDEN.allocaInst;
            auto value=llvm_part.builder.CreateLoad(llvm::Type::getInt32Ty(llvm_part.context),address,"iLoad");
            return value;
        }
    }
    // if it is a funciton call
    if (!analysis1.symbolTable.ExistSymbol(node.value)&&node.IDEN){
        // return std::numeric_limits<double>::quiet_NaN();
        std::string funcionName=node.value.substr(0,node.value.find("("));
        auto function=llvm_part.module.getFunction(funcionName);
        if (!function){
            std::runtime_error("Function not found");
        }
        std::string parameters=node.value.substr(node.value.find("(")+1,node.value.size()-1);
        std::vector<std::string> parameter;
        // spilt the parameters
        for (int i=0;i<parameters.size();i++){
            if (parameters[i]==','){
                continue;
            }
            std::string tem;
            while (parameters[i]!=','&&i<parameters.size()){
                tem+=parameters[i];
                i++;
            }
            parameter.push_back(tem);
        }
        // create the parameters
        std::vector<llvm::Value*> args;
        int i=0;
        for (auto &arg : function->args()) {
            if (getTypeString(arg.getType())=="bool"){
                args.push_back(llvm::ConstantInt::get(llvm::Type::getInt1Ty(llvm_part.context), std::stoi(parameter[i])));
            }
            else if(getTypeString(arg.getType())=="int"){
                args.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvm_part.context), std::stoi(parameter[i])));
            }
            else if(getTypeString(arg.getType())=="float"){
                args.push_back(llvm::ConstantFP::get(llvm::Type::getFloatTy(llvm_part.context), std::stof(parameter[i])));
            }
            else if(getTypeString(arg.getType())=="double"){
                args.push_back(llvm::ConstantFP::get(llvm::Type::getDoubleTy(llvm_part.context), std::stod(parameter[i])));
            }
            else if(getTypeString(arg.getType())=="char"){
                args.push_back(llvm::ConstantInt::get(llvm::Type::getInt8Ty(llvm_part.context), parameter[i][0]));
            }
            i++;
        }
        return llvm_part.builder.CreateCall(function, args);
    }
    else{
        /*
        try {
            // acoording to type ,generate different llvm::value
            if (type == "int") {
        return llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvm_part.context), std::stoi(node.value));
}
            else if (type == "float") {
    return llvm::ConstantFP::get(llvm::Type::getFloatTy(llvm_part.context), std::stof(node.value));
}
            else if (type == "double") {
    return llvm::ConstantFP::get(llvm::Type::getDoubleTy(llvm_part.context), std::stod(node.value));
}
            else if (type == "char") {
    return llvm::ConstantInt::get(llvm::Type::getInt8Ty(llvm_part.context), node.value[0]);
}
            else if (type == "bool") {
    return llvm::ConstantInt::get(llvm::Type::getInt1Ty(llvm_part.context), node.value == "true" ? 1 : 0);

}            else {
         */
                std::string str=node.value;
                try {
                    int intValue = std::stoi(str); // Convert string to int
                    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvm_part.context), intValue);  // Return an LLVM int32 value
                } catch (const std::invalid_argument&) {
                    // Not an int
                }

                // Try to convert to float
                try {
                    float floatValue = std::stof(str); // Convert string to float
                    return llvm::ConstantFP::get(llvm::Type::getFloatTy(llvm_part.context), floatValue);  // Return an LLVM float value
                } catch (const std::invalid_argument&) {
                    // Not a float
                }
                // Try to convert to double
                try {
                    double doubleValue = std::stod(str); // Convert string to double
                    return llvm::ConstantFP::get(llvm::Type::getDoubleTy(llvm_part.context), doubleValue);  // Return an LLVM double value
                } catch (const std::invalid_argument&) {
                    // Not a double
                }
                // Try to convert to bool
                if (str == "true") {
                    return llvm::ConstantInt::get(llvm::Type::getInt1Ty(llvm_part.context), 1); // Return an LLVM bool (true)
                } else if (str == "false") {
                    return llvm::ConstantInt::get(llvm::Type::getInt1Ty(llvm_part.context), 0); // Return an LLVM bool (false)
                }

                // Try to convert to char (single character)
                if (str.size() == 1) {
                    char charValue = str[0]; // Single character
                    return llvm::ConstantInt::get(llvm::Type::getInt8Ty(llvm_part.context), static_cast<int>(charValue)); // Return an LLVM char value
                }
                // If none of the conversions work, throw an exception or return nullptr
                throw std::runtime_error("Unsupported string format or type");
            }

        /*
        catch (std::exception &e){
            char ch=node.value[1];
            double value=ch;
            return llvm::ConstantFP::get(llvm_part.context, llvm::APFloat(value));
        }
         */

}
void IR_Transform::ExcpetionHandle(std::string cpppath,std::string llpath){
    // handel excepetion
    INT a=INT(0);
    a.exe(cpppath,llpath);
}
void IR_Transform::codeGeneration(std::string path) {
    return;
}
void IR_Transform::Precodition(std::string ccpath,std::string llpath){
    // preconditon
    INT a=INT(0);
    a.exe(ccpath,llpath);
    exit(0);
}