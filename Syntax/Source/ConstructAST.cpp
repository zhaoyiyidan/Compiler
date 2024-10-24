//
// Created by 赵鲲翔 on 2024/10/15.
//
#include <iostream>
#include "../header/ConstructAST.h"
// include necessary header filr

// pair<"标注的信息",“token" >
module ConstructMoule(const std::vector<std::pair<std::string, std::string>> &tokens) {
    int index = 0;
    module root;
    auto Node=ConstructFuncDel(tokens, index);
    root.Node.push_back(std::move(Node));
    // std::cout<<"moule"<<std::endl;
    return root;
}
// to construct  module ,you need following fucntion
std::unique_ptr<ASTnode> ConstructFuncDel(const std::vector<std::pair<std::string, std::string>> &tokens, int &index) {
    // std::cout<<"funcdel"<<std::endl;
    auto type=ConstructFuncType(tokens[index].second);// index here is the type of the function
    index++;
    auto name=tokens[index].second;// get the name of the function
    index++;
    if (tokens[index].second != "(") {
        LackOf("(");
    }
    index++;
    if (tokens[index].second != ")") {
        LackOf(")");
    }
    index++;
    auto body=ConstructCompoundStmt(tokens,index,tokens.size()-1);// get the body of the function
    auto functionDec = std::make_unique<FunctionDec>(std::move(type), name, std::move(body));
    return functionDec;
}
// to construct function declaration,you need following function
std::unique_ptr<ASTnode> ConstructFuncType(std:: string type) {
    // std::cout<<"functype"<<std::endl;
    return std::make_unique<FunctionType>(type);
}
std::unique_ptr<ASTnode> ConstructCompoundStmt(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex) {
    if (Lindex==Rindex) return nullptr;
    auto vector= FindPrimary(tokens,Lindex+1,Rindex-1,"{","}");
    if (vector.size()==0){
        auto vector2= FindAllExisted(tokens,Lindex,Rindex,";");
        vector2.insert(vector2.begin(),Lindex);
        std::vector<std::unique_ptr<ASTnode> > stmts;
        // problem here
        for (int i=0;i<vector2.size()-1;i++){
            auto stmt= ConstructItem(tokens,vector2[i]+1,vector2[i+1]);
            stmts.push_back(std::move(stmt));
        }
        return std::make_unique<compoundstmt>(std::move(stmts));
    }
    else{
        vector.insert(vector.begin(),Lindex);
        vector.push_back(Rindex);
        std::vector<std::unique_ptr<ASTnode> > stmts;
        for (int i=0;i<vector.size()-1;i++){
            if (i%2==1){
                stmts.push_back(std::move(ConstructCompoundStmt(tokens,vector[i],vector[i+1])));
            }
            else{
                auto vector2= FindAllExisted(tokens,vector[i],vector[i+1],";");
                vector2.insert(vector2.begin(),Lindex);
                for (int j=0;j<vector2.size()-2;j++){
                    stmts.push_back(ConstructItem(tokens,vector2[j]+1,vector2[j+1]));
                }
            }
        }
        return std::make_unique<compoundstmt>(std::move(stmts));
    }
}
// 暂时弃用
std::unique_ptr<ASTnode> ConstructItems(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex) {
    auto vector2= FindAllExisted(tokens,Lindex,Rindex,";");
    vector2.insert(vector2.begin(),Lindex);
    std::vector<std::unique_ptr<ASTnode> > stmts;
    for (int i=0;i<vector2.size()-2;i++){
        auto stmt= ConstructItem(tokens,vector2[i]+1,vector2[i+1]);
        stmts.push_back(std::move(stmt));
    }
    return std::make_unique<compoundstmt>(std::move(stmts));
}
std::unique_ptr<ASTnode> ConstructItem(const std::vector<std::pair<std::string, std::string>> &tokens,int Lindex, int Rindex) {
    auto string=DeclOrStmt(tokens,Lindex,Rindex);
    if (string=="ConstDecl"){
        return ConstructConstDecl(tokens,Lindex,Rindex);
    }
    if (string=="VarDecl"){
        return ConstructVarDecl(tokens,Lindex,Rindex);
    }
    if (string=="ReturnStmt"){
        return ConstructReturnStmt(tokens,Lindex,Rindex);
    }
    if (string=="AssignStmt"){
        return ConstructAssignStmt(tokens,Lindex,Rindex);
    }
    return nullptr;
}
std::unique_ptr<ASTnode> ConstructConstDecl(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex, int Rindex) {
    if (tokens[Lindex].second!="const"){
        LackOf("const");
    }
    // construct type
    auto type=ConstructFuncType(tokens[Lindex+1].second);
    auto vector= FindAllExisted(tokens,Lindex,Rindex,",");
    if (vector.size()==0){
        return std::make_unique<ConstDecl>(std::move(type),std::move(ConstructConstDef(tokens,Lindex+2,Rindex-1)));
    }
    else{
        vector.push_back(Rindex);
        std::vector<std::unique_ptr<ASTnode>> ConstDefs;
        ConstDefs.push_back(ConstructConstDef(tokens,Lindex+2,vector[0]-1));
        // problem here
        for (int i=0;i<vector.size()-2;i++){
            auto ConstDef=ConstructConstDef(tokens,vector[i]+1,vector[i+1]-1);
            ConstDefs.push_back(std::move(ConstDef));
        }
        return std::make_unique<ConstDecl>(std::move(type),std::move(ConstructConstDef(tokens,vector[vector.size()-1]+1,Rindex-1)),std::move(ConstDefs));
    }
}
std::unique_ptr<ASTnode> ConstructConstDef(const std::vector<std::pair<std::string, std::string>> &tokens,int Lindex, int Rindex) {
    if (tokens[Lindex].first!="IDENT"){
        LackOf("IDENT");
    }
    if (tokens[Lindex+1].second!="="){
        LackOf("=");
    }
    return std::make_unique<ConstDef>(tokens[Lindex].second,ConstructExp(tokens,Lindex+2,Rindex));
}
std::unique_ptr<ASTnode> ConstructVarDecl(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex, int Rindex) {
    auto type=ConstructFuncType(tokens[Lindex].second);
    auto vector= FindAllExisted(tokens,Lindex,Rindex,",");
    if (vector.size()==0){
        return std::make_unique<VarDecl>(std::move(type),std::move(ConstructVarDef(tokens,Lindex+1,Rindex-1)));
    }
    else{
        vector.push_back(Rindex);
        std::vector<std::unique_ptr<ASTnode>> VarDefs;
        VarDefs.push_back(ConstructVarDef(tokens,Lindex+1,vector[0]-1));
        for (int i=0;i<vector.size()-2;i++){
            auto VarDef=ConstructVarDef(tokens,vector[i]+1,vector[i+1]-1);
            VarDefs.push_back(std::move(VarDef));
        }
        return std::make_unique<VarDecl>(std::move(type),std::move(ConstructVarDef(tokens,vector[vector.size()-1]+1,Rindex-1)),std::move(VarDefs));
    }
}
std::unique_ptr<ASTnode> ConstructVarDef(const std::vector<std::pair<std::string, std::string>> &tokens,int Lindex, int Rindex) {
    if (tokens[Lindex].first!="IDENT"){
        LackOf("IDENT");
    }
    if (tokens[Lindex+1].second!="="){
    LackOf("=");
    }
    return std::make_unique<VarDef>(tokens[Lindex].second,ConstructExp(tokens,Lindex+2,Rindex));
}

std::unique_ptr<ASTnode> ConstructReturnStmt(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex) {
    if (tokens[Lindex].second!="return"){
        LackOf("return");
    }
    return std::make_unique<ReturnStmt>(ConstructExp(tokens,Lindex+1,Rindex-1));
}

std::unique_ptr<ASTnode> ConstructAssignStmt(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex) {
if (tokens[Lindex].first!="IDENT"){
LackOf("IDENT");
}
if (tokens[Lindex+1].second!="="){
LackOf("=");
}
return std::make_unique<AssignStmt>(tokens[Lindex].second, ConstructExp(tokens, Lindex+2, Rindex-1));
}
// exp

std::unique_ptr<ASTnode> ConstructExp(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex) {

    auto lorExp=ConstructLOrExp(tokens, Lindex, Rindex);
    return std::make_unique<Expression>(std::move(lorExp));
}
// here we need to consider recursion
std::unique_ptr<ASTnode> ConstructLOrExp(const std::vector<std::pair<std::string, std::string>> &tokens, int LeftIndex,int RightIndex) {
    auto pair= FindExisted(tokens,LeftIndex,RightIndex,"||");// to check if there is a "||"
    // if there is a "||"
    if (pair.first){
        auto pair2=FindExisted(tokens,LeftIndex,pair.second-1,"||");// to check if there is a "||"
        std::unique_ptr<ASTnode> expression= nullptr;
        if (pair2.first){
            expression=std::move(ConstructLOrExp(tokens,LeftIndex,pair.second-1));
        }
        else{
            expression=std::move(ConstructLAndExp(tokens,LeftIndex,pair.second-1));
        }
        auto LAndExp=std::move(ConstructLAndExp(tokens,pair.second+1,RightIndex));
        return std::make_unique<LOrExp>(std::move(expression),std::move(LAndExp));
    }
    else{
        return ConstructLAndExp(tokens,LeftIndex,RightIndex);
    }
}
std::unique_ptr<ASTnode> ConstructLAndExp(const std::vector<std::pair<std::string, std::string>> &tokens, int LeftIndex,int RightIndex) {
    auto pair= FindExisted(tokens,LeftIndex,RightIndex,"&&");// to check if there is a "&&"
    // if there is a "&&"
    if (pair.first){
        auto pair2=FindExisted(tokens,LeftIndex,pair.second-1,"&&");// to check if there is a "&&"
        std::unique_ptr<ASTnode> expression= nullptr;
        if (pair2.first){
            expression=std::move(ConstructLAndExp(tokens,LeftIndex,pair.second-1));
        }
        else{
            expression=std::move(ConstructEqExp(tokens,LeftIndex,pair.second-1));
        }
        auto EqExp=std::move(ConstructEqExp(tokens,pair.second+1,RightIndex));
        return std::make_unique<LAndExp>(std::move(expression),std::move(EqExp));
    }
    else{
        return std::move(ConstructEqExp(tokens,LeftIndex,RightIndex));
    }
}
std::unique_ptr<ASTnode> ConstructEqExp(const std::vector<std::pair<std::string, std::string>> &tokens, int LeftIndex,int RightIndex) {
    auto pair1= FindExisted(tokens,LeftIndex,RightIndex,"==");// to check if there is a "=="
    auto pair2= FindExisted(tokens,LeftIndex,RightIndex,"!=");// to check if there is a "!="
    if (pair1.first || pair2.first){
        std::string op;
        int thepos;
        if (pair1.second>pair2.second){
            op="!=";
            thepos=pair2.second;
        }
        else{
            op="==";
            thepos=pair1.second;
        }
        auto pair3=FindExisted(tokens,LeftIndex,thepos-1,"==");// to check if there is a "=="
        auto pair4=FindExisted(tokens,LeftIndex,thepos-1,"!=");// to check if there is a "!="
        std::unique_ptr<ASTnode> expression= nullptr;
        if (pair3.first || pair4.first){
            expression=std::move(ConstructEqExp(tokens,LeftIndex,thepos-1));
        }
        else{
            expression=std::move(ConstructRelExp(tokens,LeftIndex,thepos-1));
        }
        auto RelExp=std::move(ConstructRelExp(tokens,thepos+1,RightIndex));
        return std::make_unique<EqExp>(std::move(expression),std::move(RelExp),op);
    }
    else{
        return std::move(ConstructRelExp(tokens,LeftIndex,RightIndex));
    }
}
std::unique_ptr<ASTnode> ConstructRelExp(const std::vector<std::pair<std::string, std::string>> &tokens,int Lindex, int Rindex) {
    // similar to the above
    auto vector=std::vector<std::string>{"<",">","<=",">="};
    auto pair=FindMulExisted(tokens,Lindex,Rindex,vector);
    vector.clear();
    vector.shrink_to_fit();

    if (pair.first!="null"){
        auto pair2=FindMulExisted(tokens,Lindex,pair.second-1,vector);
        if (pair2.first!="null"){
            auto expression=std::move(ConstructRelExp(tokens,Lindex,pair.second-1));
            auto AddExp=std::move(ConstructAddExp(tokens,pair.second+1,Rindex));
            return std::make_unique<RelExp>(std::move(expression),std::move(AddExp),pair.first);
        }
        else{
            auto AddExp=std::move(ConstructAddExp(tokens,Lindex,pair.second-1));
            auto AddExp2=std::move(ConstructAddExp(tokens,pair.second+1,Rindex));
            return std::make_unique<RelExp>(std::move(AddExp),std::move(AddExp2),pair.first);
        }
    }
    else{
        return std::move(ConstructAddExp(tokens,Lindex,Rindex));
    }
}
std::unique_ptr<ASTnode> ConstructAddExp(const std::vector<std::pair<std::string, std::string>> &tokens,int Lindex, int Rindex) {
    auto vector=std::vector<std::string>{"+","-"};
    auto pair=FindMulExisted(tokens,Lindex,Rindex,vector);
    vector.clear();
    vector.shrink_to_fit();
    if (pair.first!="null"){
        auto pair2=FindMulExisted(tokens,Lindex,pair.second-1,vector);
        if (pair2.first!="null"){
            auto expression=std::move(ConstructAddExp(tokens,Lindex,pair.second-1));
            auto MulExp=std::move(ConstructMulExp(tokens,pair.second+1,Rindex));
            return std::make_unique<AddExp>(std::move(expression),std::move(MulExp),pair.first);
        }
        else{
            auto MulExp=std::move(ConstructMulExp(tokens,Lindex,pair.second-1));
            auto MulExp2=std::move(ConstructMulExp(tokens,pair.second+1,Rindex));
            return std::make_unique<AddExp>(std::move(MulExp),std::move(MulExp2),pair.first);
        }
    }
    else{
        return std::move(ConstructMulExp(tokens,Lindex,Rindex));
    }
}
std::unique_ptr<ASTnode> ConstructMulExp(const std::vector<std::pair<std::string, std::string>> &tokens,int Lindex, int Rindex) {
    // similar to the above
    auto vector=std::vector<std::string>{"*","/","%"};
    auto pair=FindMulExisted(tokens,Lindex,Rindex,vector);
    vector.clear();
    vector.shrink_to_fit();
    if (pair.first!="null"){
        auto pair2=FindMulExisted(tokens,Lindex,pair.second-1,vector);
        if (pair2.first!="null"){
            auto expression=std::move(ConstructMulExp(tokens,Lindex,pair.second-1));
            auto Unary=std::move(ConstructUnaryExp(tokens,pair.second+1,Rindex));
            return std::make_unique<MulExp>(std::move(expression),std::move(Unary),pair.first);
        }
        else{
            auto UnaryExp=std::move(ConstructUnaryExp(tokens,Lindex,pair.second-1));
            auto UnaryExp2=std::move(ConstructMulExp(tokens,pair.second+1,Rindex));
            return std::make_unique<MulExp>(std::move(UnaryExp),std::move(UnaryExp2),pair.first);
        }
    }
    else{
        return std::move(ConstructUnaryExp(tokens,Lindex,Rindex));
    }
}
std::unique_ptr<ASTnode> ConstructUnaryExp(const std::vector<std::pair<std::string, std::string>> &tokens,int Lindex, int Rindex) {

    if (Lindex==Rindex){
        return std::move(ConstructPrimaryExp(tokens,Lindex,Rindex));
    } // here is the problem of the recursion
    auto vector=std::vector<std::string>{"-","!","+"};
    auto pair=FindMulExisted(tokens,Lindex,Rindex,vector);
    vector.clear();
    vector.shrink_to_fit();
    if (pair.first!="null"){
        auto unaryExp=std::move(ConstructUnaryExp(tokens,pair.second+1,Rindex));
        auto expreesion=std::move(ConstructUnaryOp(tokens,Lindex,pair.second));
        return std::make_unique<UnaryExp>(std::move(expreesion),std::move(unaryExp));
    }
    else{
        return std::move(ConstructPrimaryExp(tokens,Lindex,Rindex));
    }
    return nullptr;

}
std::unique_ptr<ASTnode> ConstructUnaryOp(const std::vector<std::pair<std::string, std::string>> &tokens,int Lindex, int Rindex) {
    return std::make_unique<UnaryOp>(tokens[Lindex].second);
}
// temporary solution
std::unique_ptr<ASTnode> ConstructPrimaryExp(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex, int Rindex) {
    // std::cout<<"primaryexp"<<std::endl;
    if (Lindex==Rindex){
        return std::make_unique<IntegerLiteral>(tokens[Lindex].second);
    }
    if (tokens[Lindex].second=="("){
        // find ")"
        auto pair= FindExisted(tokens,Lindex,Rindex,")");
        return ConstructExp(tokens,Lindex+1,pair.second-1);
    }
    return nullptr;
}
// end of exp
