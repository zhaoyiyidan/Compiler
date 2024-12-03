//
// Created by 赵鲲翔 on 2024/10/15.
//
#include <iostream>
#include "../header/ConstructAST.h"
// include necessary header filr

// pair<"标注的信息",“token" >
module ConstructMoule(const std::vector<std::pair<std::string, std::string>> &tokens) {
   int index=0;
   module the_module;
   while(index<tokens.size()-1){
       auto first=tokens[index].first;
       auto second=tokens[index+1].first;
       auto third=tokens[index+2].second;
       if (first=="KeyWord"&&second=="IDEN"&&third=="("){
           // construct FunctionDecl
           auto pair=FindCorrsponding(tokens,index,tokens.size()-1,"{","}");
           the_module.Node.push_back(ConstructFuncDel(tokens,index,pair.second));
           index=pair.second+1;
       }
       else if (first=="KeyWord"&&second=="IDEN"&&third=="{"){
           auto pair= FindCorrsponding(tokens,index,tokens.size()-1,"{","}");
           the_module.Node.push_back(ConstructStructDecl(tokens,index,pair.second));
           index=pair.second+2;
       }
       else{
           // construct global Variable
           auto pair= FindLeftExisted(tokens,index,tokens.size()-1,";");
           the_module.Node.push_back(ConstructItem(tokens,index,pair.second));
           index=pair.second+1;
       }
   }
    return the_module;
}
// to construct  module ,you need following fucntion
std::unique_ptr<ASTnode> ConstructFuncDel(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex) {
    // index should be function type
    auto type=ConstructFuncType(tokens[Lindex].second);// index here is the type of the function
    auto name=tokens[Lindex+1].second;// get the name of the function
    auto pair= FindCorrsponding(tokens,Lindex+2,Rindex,"(",")");// find the parameters
    auto parameters=ConstructFunctionParameters(tokens,Lindex+2,pair.second);// get the parameters of the function
    auto body=ConstructCompoundStmt(tokens,pair.second+1,Rindex);// get the body of the function
    return std::make_unique<FunctionDec>(std::move(type),name,std::move(parameters),std::move(body));
}
// to construct function declaration,you need following function
std::unique_ptr<ASTnode> ConstructFuncType(std:: string type) {
    // std::cout<<"functype"<<std::endl;
    return std::make_unique<FunctionType>(type);
}
std::unique_ptr<ASTnode> ConstructCompoundStmt(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex) {

    std::vector<std::unique_ptr<ASTnode> > stmts;
    int index=Lindex+1;
    while (index<Rindex){
        std::string a=tokens[index].second;
        if(a=="while"){
            auto tem= FindCorrsponding(tokens,index,Rindex,"{","}");
            stmts.push_back(ConstructWhileStmt(tokens,index,tem.second));
            index=tem.second+1;
        }
        else if (a=="for"){
            auto tem= FindCorrsponding(tokens,index,Rindex,"{","}");
            stmts.push_back(ConstructForStmt(tokens,index,tem.second));
            index=tem.second+1;
        }
        else if (a=="if"){
            auto tem= FindCorrsponding(tokens,index,Rindex,"{","}");
            if (tokens[tem.second+1].second=="else" && tokens[tem.second+2].second!="if" ){
                auto pair= FindCorrsponding(tokens,tem.second+1,Rindex,"{","}");
                stmts.push_back(ConstructIFStmt(tokens,index,pair.second));
                index=pair.second+1;
            }
            else{
            stmts.push_back(ConstructIFStmt(tokens,index,tem.second));
            index=tem.second+1;
            }
        }
        // else if as a new if statement
        else if (a=="else" && tokens[index+1].second=="if"){
            auto tem= FindCorrsponding(tokens,index,Rindex,"{","}");
            if (tokens[tem.second+1].second=="else" && tokens[tem.second+2].second!="if" ){
                auto pair= FindCorrsponding(tokens,tem.second+1,Rindex,"{","}");
                stmts.push_back(ConstructIFStmt(tokens,index,pair.second));
                index=pair.second+1;
            }
            else{
                stmts.push_back(ConstructIFStmt(tokens,index,tem.second));
                index=tem.second+1;
            }
        }
        else if (a=="{"){
            auto tem= FindCorrsponding(tokens,index,Rindex,"{","}");
            stmts.push_back(ConstructCompoundStmt(tokens,index,tem.second));
            index=tem.second+1;
        }
        else{
            auto tem= FindLeftExisted(tokens,index,Rindex,";");
            stmts.push_back(ConstructItem(tokens,index,tem.second));
            index=tem.second+1;
        }
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
    if (string=="increment"){
        // i++ same as i=i+1;
        std::vector<std::pair<std::string ,std::string > >tem;
        std::string IDEN=tokens[Lindex].second;
        tem.push_back({"IDEN",IDEN});
        tem.push_back({"OP","="});
        tem.push_back({"IDEN",IDEN});
        tem.push_back({"OP","+"});
        tem.push_back({"NUM","1"});
        tem.push_back({"SEP",";"});
        return ConstructAssignStmt(tem,0,5);
    }
    if (string=="decrement"){
        // i++ same as i=i+1;
        std::vector<std::pair<std::string ,std::string > >tem;
        std::string IDEN=tokens[Lindex].second;
        tem.push_back({"IDEN",IDEN});
        tem.push_back({"OP","="});
        tem.push_back({"IDEN",IDEN});
        tem.push_back({"OP","-"});
        tem.push_back({"NUM","1"});
        tem.push_back({"SEP",";"});
        return ConstructAssignStmt(tem,0,5);
    }
    if (string=="continue"){
        return ConstructContinueStmt(tokens,Lindex,Rindex);
    }
    if (string=="break"){
        return ConstructBreakStmt(tokens,Lindex,Rindex);
    }
    return nullptr;
}
std::unique_ptr<ASTnode> ConstructConstDecl(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex, int Rindex) {
    if (tokens[Lindex].second!="const"){
        LackOf("const");
    }
    // construct type
    auto type=ConstructFuncType(tokens[Lindex+1].second);
    auto vector= FindAllExistedIgnoreBracket(tokens,Lindex,Rindex,",");
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
    if (tokens[Lindex].first=="IDEN"&& tokens[Lindex+1].second=="["){
        auto pair= FindCorrsponding(tokens,Lindex,Rindex,"[","]");
        auto ArraySize=ConstructExp(tokens,Lindex+2,pair.second-1);
        std::vector<std::unique_ptr<ASTnode>> array;
        if (pair.second<Rindex){
            auto vector= FindAllExisted(tokens,pair.second+1,Rindex,",");
            vector.push_back(Rindex);
            vector.insert(vector.begin(),pair.second+2);
            for (int i=0;i<vector.size()-1;i++){
                auto exp=ConstructExp(tokens,vector[i]+1,vector[i+1]-1);
                array.push_back(std::move(exp));
            }
        }
        return std::make_unique<ConstDef>(tokens[Lindex].second, nullptr,std::move(ArraySize),std::move(array));
    }
    return std::make_unique<ConstDef>(tokens[Lindex].second,ConstructExp(tokens,Lindex+2,Rindex));
}
std::unique_ptr<ASTnode> ConstructVarDecl(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex, int Rindex) {
    auto type=ConstructFuncType(tokens[Lindex].second);
    auto vector= FindAllExistedIgnoreBracket(tokens,Lindex,Rindex,",");
    if (vector.size()==0){
        return std::make_unique<VarDecl>(std::move(type),std::move(ConstructVarDef(tokens,Lindex+1,Rindex-1)));
    }
    else{
        vector.push_back(Rindex);
        vector.insert(vector.begin(),Lindex);
        std::vector<std::unique_ptr<ASTnode>> VarDefs;
        for (int i=0;i<vector.size()-1;i++){
            auto VarDef=ConstructVarDef(tokens,vector[i]+1,vector[i+1]-1);
            VarDefs.push_back(std::move(VarDef));
        }
        return std::make_unique<VarDecl>(std::move(type), nullptr,std::move(VarDefs));
    }
}
std::unique_ptr<ASTnode> ConstructVarDef(const std::vector<std::pair<std::string, std::string>> &tokens,int Lindex, int Rindex) {
        // rindex is not ;
    if (tokens[Lindex].first=="IDEN"&&tokens[Lindex+1].second=="["){
        auto pair= FindCorrsponding(tokens,Lindex,Rindex,"[","]");
        auto ArraySize=ConstructExp(tokens,Lindex+2,pair.second-1);
        std::vector<std::unique_ptr<ASTnode>> array;
        if (pair.second<Rindex){
            auto vector= FindAllExisted(tokens,pair.second+1,Rindex,",");
            vector.push_back(Rindex);
            vector.insert(vector.begin(),pair.second+2);
            for (int i=0;i<vector.size()-1;i++){
                auto exp=ConstructExp(tokens,vector[i]+1,vector[i+1]-1);
                array.push_back(std::move(exp));
            }
        }
        return std::make_unique<VarDef>(tokens[Lindex].second, nullptr,std::move(ArraySize),std::move(array));
    }
    else {
        auto exp = ConstructExp(tokens, Lindex + 2, Rindex);
        if (exp) {
            return std::make_unique<VarDef>(tokens[Lindex].second, std::move(exp));
        }
        return std::make_unique<VarDef>(tokens[Lindex].second, nullptr);

    }
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
// not use the exp below
std::unique_ptr<ASTnode> ConstructExp(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex) {
    if (Lindex>Rindex){
        return nullptr;
    }
    auto token= infixToPostfixs(tokens,Lindex,Rindex);
    return ConstructEXP(token);

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
        if (tokens[Lindex].first=="IDEN"){
            return std::make_unique<LValue>(tokens[Lindex].second);
        }
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

// antoher way to construct exp
std::unique_ptr<ASTnode> ConstructEXP(const std::vector<std::pair<std::string,std::string> > &tokens) {
    std::stack<std::unique_ptr<ASTnode>> stack;
    if (tokens.size()==1){
        if (tokens[0].first=="IDEN" || tokens[0].first=="FunctionCall"){
            return std::make_unique<EXP>(tokens[0].second,true);
        }
        else{
        return std::make_unique<EXP>(tokens[0].second, false);
        }
    }
    for(auto &token:tokens){
        if (isdigit(token.second[0])){
            stack.push(std::make_unique<EXP>(nullptr,token.second, nullptr));
        }
        else if (token.first=="IDEN" || token.first=="FunctionCall"){
            stack.push(std::make_unique<EXP>(token.second,true));
        }
        else if (token.second=="!"){
            auto operand=std::move(stack.top());
            stack.pop();
            stack.push(std::make_unique<EXP>(nullptr,"!",std::move(operand)));
        }
        else {
            auto right = std::move(stack.top());
            stack.pop();
            auto left = std::move(stack.top());
            stack.pop();
            auto node = std::make_unique<EXP>(std::move(left),token.second,std::move(right));
            stack.push(std::move(node));
        }
    }
    return std::move(stack.top());
}
// control node
std::unique_ptr<ASTnode> ConstructWhileStmt(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex) {
    if (tokens[Lindex].second!="while"){
        LackOf("while");
    }
    auto pair= FindCorrsponding(tokens,Lindex,Rindex,"(",")");
    auto condition=ConstructExp(tokens,Lindex+2,pair.second-1);
    auto body=ConstructCompoundStmt(tokens,pair.second+1,Rindex);
    return std::make_unique<WhileStmt>(std::move(condition),std::move(body));
}
// the increment part should be considered in ConstructItem
std::unique_ptr<ASTnode> ConstructForStmt(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex){
    // the tokens[Lindex] should be for
    auto pair=FindLeftExisted(tokens,Lindex,Rindex,";");
    auto init=ConstructItem(tokens,Lindex+2,pair.second);
    auto pair2=FindLeftExisted(tokens,pair.second+1,Rindex,";");
    auto condition=ConstructExp(tokens,pair.second+1,pair2.second-1);//
    auto pair3=FindLeftExisted(tokens,pair2.second+1,Rindex,")");
    auto update=ConstructItem(tokens,pair2.second+1,pair3.second);
    auto body=ConstructCompoundStmt(tokens,pair3.second+1,Rindex);
    return std::make_unique<ForStmt>(std::move(init),std::move(condition),std::move(update),std::move(body));
}
// do not consider the else part now
std::unique_ptr<ASTnode> ConstructIFStmt(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex){
    // Lindex should be if
    auto pair= FindCorrsponding(tokens,Lindex,Rindex,"(",")");
    auto pair3= FindLeftExisted(tokens,Lindex,Rindex,"(");
    auto condition=ConstructExp(tokens,pair3.second+1,pair.second-1);// the condition
    auto pair2= FindCorrsponding(tokens,pair.second+1,Rindex,"{","}");
    auto body=ConstructCompoundStmt(tokens,pair.second+1,pair2.second);

    if (pair2.second==Rindex) {
        return std::make_unique<IFStmt>(std::move(condition), std::move(body), nullptr);
    }
    else {
        if (tokens[pair2.second+1].second=="else"){
            auto body2=ConstructCompoundStmt(tokens,pair2.second+1,Rindex);
            // do a dynmaic cast
            auto elsebody=dynamic_cast<compoundstmt*>(body2.get());
            elsebody->ASTNodeType="ELseStmt";
            return std::make_unique<IFStmt>(std::move(condition), std::move(body), std::move(body2));
        }
        std::runtime_error("error in ConstructIFStmt");
    }
    // if (){} else{}
}

std::unique_ptr<ASTnode> ConstructBreakStmt(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex){
    if (tokens[Lindex].second!="break"){
        LackOf("break");
    }
    return std::make_unique<BreakStmt>();
}
std::unique_ptr<ASTnode> ConstructContinueStmt(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex){
    if (tokens[Lindex].second!="continue"){
        LackOf("continue");
    }
    return std::make_unique<ContinueStmt>();
}
std::vector<std::unique_ptr<ASTnode> > ConstructFunctionParameters(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex){
    // (-------)
    std::vector<std::unique_ptr<ASTnode>> parameters;
    if (tokens[Lindex].second!="("){
        LackOf("(");
    }
    if (tokens[Rindex].second!=")"){
        LackOf(")");
    }
    if (Lindex+1==Rindex){
        return parameters;// which mean no paramenters
    }
    auto vector= FindAllExisted(tokens,Lindex+1,Rindex,",");
    vector.insert(vector.begin(),Lindex);
    vector.push_back(Rindex);
    for (int i=0;i<vector.size()-1;i++){
        auto parameter=ConstructParameter(tokens,vector[i]+1,vector[i+1]);
        parameters.push_back(std::move(parameter));
    }
    return parameters;
}
std::unique_ptr<ASTnode> ConstructParameter(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex){
   auto type=ConstructFuncType(tokens[Lindex].second);
   auto var=std::make_unique<VarDef>(tokens[Lindex+1].second,nullptr);
   return std::make_unique<VarDecl>(std::move(type),std::move(var));
}
std::unique_ptr<ASTnode> ConstructStructDecl(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex){
    if (tokens[Lindex].second!="struct"){
        LackOf("struct");
    }
    auto name=tokens[Lindex+1].second;
    auto body=ConstructStructBody(tokens,Lindex+2,Rindex);
    return std::make_unique<StructDecl>(name,std::move(body));
}
std::unique_ptr<ASTnode> ConstructStructBody(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex){
    // lindex is {
    std::vector<std::unique_ptr<ASTnode>> members;
    int index=Lindex+1;
    while (index<Rindex){
        if (tokens[index].first=="KeyWord"&&tokens[index+1].first=="IDEN"&&tokens[index+2].second=="("){
            auto pair= FindCorrsponding(tokens,index,Rindex,"{","}");
            members.push_back(ConstructFuncDel(tokens,index,pair.second));
            index=pair.second+1;
        }
        else{
        auto pair= FindLeftExisted(tokens,index,Rindex,";");
        members.push_back(ConstructVarDecl(tokens,index,pair.second));
        index=pair.second+1;
        }
    }
    return std::make_unique<StructBody>(std::move(members));
}
