//
// Created by 赵鲲翔 on 2024/10/15.
//
#include <iostream>
#include "../header/ConstructAST.h"
// include necessary header filr
#include "../header/Type/IntegerLiteral.h"
#include "../header/Declaration/FunctionDec.h"

// pair<"标注的信息",“token" >
module ConstructAST::ConstructMoule(const std::vector<std::pair<std::string, std::string>> &tokens) {
    int index = 0;
    module root;
    auto Node=ConstructFuncDel(tokens, index);
    root.Node.push_back(std::move(Node));
    // std::cout<<"moule"<<std::endl;
    return root;
}
// to construct  module ,you need following fucntion
std::unique_ptr<ASTnode> ConstructAST::ConstructFuncDel(const std::vector<std::pair<std::string, std::string>> &tokens, int &index) {
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
    auto body=ConstructCompoundStmt(tokens,index);// get the body of the function
    auto functionDec = std::make_unique<FunctionDec>(std::move(type), name, std::move(body));
    return functionDec;
}
// to construct function declaration,you need following function
std::unique_ptr<ASTnode> ConstructAST::ConstructFuncType(std:: string type) {
    // std::cout<<"functype"<<std::endl;
    return std::make_unique<FunctionType>(type);
}
std::unique_ptr<ASTnode> ConstructAST::ConstructCompoundStmt(const std::vector<std::pair<std::string, std::string>> &tokens, int &index) {
    if (tokens[index].second != "{") {
        LackOf("{");
    }
    index++;
    auto stmt=ConstructStmt(tokens, index);
    auto body = std::make_unique<compoundstmt>(std::move(stmt));
    if (tokens[index].second != "}") {
        LackOf("}");
    }
    index++;
    return body;
}
std::unique_ptr<ASTnode> ConstructAST::ConstructStmt(const std::vector<std::pair<std::string, std::string>> &tokens, int &index) {
    if (tokens[index].second != "return") {
        LackOf("return");
    }
    index++;
    auto pair= FindLeftExisted(tokens, index, tokens.size()-1,";");
    auto exp=ConstructExp(tokens, index,pair.second-1);
    index++;
    if (tokens[index].second != ";") {
        LackOf(";");
    }

    return std::make_unique<Stmt>(std::move(exp));
}
std::unique_ptr<ASTnode> ConstructAST::ConstructExp(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex) {

    auto lorExp=ConstructLOrExp(tokens, Lindex, Rindex);
    return std::make_unique<Expression>(std::move(lorExp));
}
// here we need to consider recursion
std::unique_ptr<ASTnode> ConstructAST::ConstructLOrExp(const std::vector<std::pair<std::string, std::string>> &tokens, int LeftIndex,int RightIndex) {
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
std::unique_ptr<ASTnode> ConstructAST::ConstructLAndExp(const std::vector<std::pair<std::string, std::string>> &tokens, int LeftIndex,int RightIndex) {
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
std::unique_ptr<ASTnode> ConstructAST::ConstructEqExp(const std::vector<std::pair<std::string, std::string>> &tokens, int LeftIndex,int RightIndex) {
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
std::unique_ptr<ASTnode> ConstructAST::ConstructRelExp(const std::vector<std::pair<std::string, std::string>> &tokens,int Lindex, int Rindex) {
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
std::unique_ptr<ASTnode> ConstructAST::ConstructAddExp(const std::vector<std::pair<std::string, std::string>> &tokens,int Lindex, int Rindex) {
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
std::unique_ptr<ASTnode> ConstructAST::ConstructMulExp(const std::vector<std::pair<std::string, std::string>> &tokens,int Lindex, int Rindex) {
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
// consider the boundary of the recursion
std::unique_ptr<ASTnode> ConstructAST::ConstructUnaryExp(const std::vector<std::pair<std::string, std::string>> &tokens,int Lindex, int Rindex) {

    if (Lindex==Rindex){
        return std::move(ConstructPrimaryExp(tokens,Lindex,Rindex));
    } // here is the problem of the recursion
    auto vector=std::vector<std::string>{"-","!","+",")"};
    auto pair=FindMulExisted(tokens,Lindex,Rindex,vector);
    vector.clear();
    vector.shrink_to_fit();
    if (pair.first!="null"){
        auto unaryExp=std::move(ConstructUnaryExp(tokens,pair.second+1,Rindex));
        std::unique_ptr<ASTnode> expreesion= nullptr;
        if (pair.first==")"){
            expreesion=std::move(ConstructPrimaryExp(tokens,Lindex,pair.second));
        } else{
            expreesion=std::move(ConstructUnaryOp(tokens,Lindex,pair.second));
        }
        return std::make_unique<UnaryExp>(std::move(expreesion),std::move(unaryExp));
    }
    return nullptr;

}
std::unique_ptr<ASTnode> ConstructAST::ConstructUnaryOp(const std::vector<std::pair<std::string, std::string>> &tokens,int Lindex, int Rindex) {
    return std::make_unique<UnaryOp>(tokens[Lindex].second);
}
std::unique_ptr<ASTnode> ConstructAST::ConstructPrimaryExp(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex, int Rindex) {
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
// here is some helper function
// find the rightest one
std::pair<bool,int> ConstructAST::FindExisted(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str) {
    auto a=std::make_pair(false,-1);
    for(int i=Lindex;i<Rindex+1;i++){
        if(tokens[i].second==str){
            a.first=true;
            a.second=i;
        }
    }
    return a;
}
std::pair<bool,int> ConstructAST::FindLeftExisted(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str) {
    auto a=std::make_pair(false,-1);
    for(int i=Lindex;i<Rindex+1;i++){
        if(tokens[i].second==str){
            a.first=true;
            a.second=i;
            return a;
        }
    }
    return a;
}

// find the rightest one
std::pair<std::string,int> ConstructAST::FindMulExisted(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,const std::vector<std::string> &str) {
    std::pair<std::string ,int> a=std::make_pair("null",-1);
    for(int i=Lindex;i<Rindex+1;i++){
        for(auto &s:str){
            if(tokens[i].second==s){
                a.first=tokens[i].second;
                a.second=i;
            }
        }
    }
    return a;
}
bool ConstructAST::ExistPrimaryOrUnaryOp (const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex) {
    if (ExistPrimary(tokens,Lindex,Rindex)||ExistUnaryOp(tokens,Lindex,Rindex)){
        return true;
    }
    return false;
}
bool ConstructAST::ExistUnaryOp(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex) {
    for(int i=Lindex;i<Rindex+1;i++){
        if(tokens[i].second=="-"||tokens[i].second=="!"||tokens[i].second=="+"){
            return true;
        }
    }
    return false;
}
bool ConstructAST::ExistPrimary(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex) {
    if (Lindex==Rindex&&tokens[Lindex].first=="IntegerLiteral"){
        return true;
    }
    for(int i=Lindex;i<Rindex+1;i++){
        if(tokens[i].second=="("){
            return true;
        }
    }
    return false;
}

// here is the implementation of error function
std::string ConstructAST::LackOf(std::string str) {
    return "str";
}