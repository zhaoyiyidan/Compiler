//
// Created by 赵鲲翔 on 2024/10/23.
#include "../header/HelperFunction.h"
// here is some helper function
// find the rightest one
std::pair<bool,int> FindExisted(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str) {
    auto a=std::make_pair(false,-1);
    for(int i=Lindex;i<Rindex+1;i++){
        if(tokens[i].second==str){
            a.first=true;
            a.second=i;
        }
    }
    return a;
}
// Find the Leftest one
std::pair<bool,int> FindLeftExisted(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str) {
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
// find all the existed one
std::vector<int> FindAllExisted(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str) {
    std::vector<int> a;
    for(int i=Lindex;i<Rindex+1;i++){
        if(tokens[i].second==str){
            a.push_back(i);
        }
    }
    return a;
}
// find the rightest one
std::pair<std::string,int> FindMulExisted(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,const std::vector<std::string> &str) {
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
// need to be refractor
//
std::string ReturnOrAssign(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex) {

    if(tokens[Lindex].second=="return"){
        return "ReturnStmt";
    }
    if (tokens[Lindex].first=="IDEN"&&tokens[Lindex+1].second=="="){
        return "AssignStmt";
    }
    return "null";
}
//
std::string ConstDeclOrVarDecl(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex,int Rindex) {
    if (tokens[Lindex].second=="const"){
        return "ConstDecl";
    }
    // temporary solution
    if (tokens[Lindex].first=="KeyWord"&&tokens[Lindex+1].first=="IDEN"){
        return "VarDecl";
    }
    return "null";
}
std::string DeclOrStmt(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex, int Rindex) {
    auto string=ConstDeclOrVarDecl(tokens,Lindex,Rindex);
    if (string!="null"){
        return string;
    }
    else{
        auto string2=ReturnOrAssign(tokens,Lindex,Rindex);
        if (string2!="null"){
            return string2;
        }
    }
    return "null";
}
// here is the implementation of error function
std::string LackOf(std::string str) {
    return str;
}