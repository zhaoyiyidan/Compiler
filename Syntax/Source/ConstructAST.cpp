//
// Created by 赵鲲翔 on 2024/10/15.
//

#include "../header/ConstructAST.h"
// include necessary header filr
#include "../header/Type/IntegerLiteral.h"
std::unique_ptr<ASTnode> ConstructAST::constructVarDec(const std::vector<std::pair<std::string, std::string>> &tokens,int& index) {
    // VarDec: Type ID
    if (tokens[index].second=="int"){
        index++;
        std::string name=tokens[index].second;
        index++;
        VarDec varDec;
        varDec.name=name;
        return std::make_unique<VarDec>(varDec);
    }
}
std::unique_ptr<ASTnode> ConstructAST::constructAssign(const std::vector<std::pair<std::string, std::string>> &tokens,int& index) {
    // Lvalue "=" Expression
    constructVarDec(tokens,index);
}
std::unique_ptr<ASTnode> ConstructAST::constructType(std::string type) {
    if (type == "int") {
        IntegerLiteral intLiteral(0);
        return std::make_unique<IntegerLiteral>(intLiteral);
    }
}
std::unique_ptr<ASTnode> ConstructAST::constructCompoundStmt(const std::vector<std::pair<std::string,std::string> > &tokens,int& index) {
    // this one is a little bit complex
    // int a=3; temmporary solution for now
    constructAssign(tokens,index);
}
// the paremeter index is the index of the first token of the function declare,  use reference to change the value of index
std::unique_ptr<ASTnode> ConstructAST::constructFunction(const std::vector<std::pair<std::string,std::string> > &tokens,int& index) {
    std::unique_ptr<ASTnode> type=std::move(constructType(tokens[index].second));// tokens[index] is the type of the function
    index++;
    std::string name=tokens[index].second;// tokens[index+1] is the name of the function
    // here temp ignore the parameter list
    index+=4;
    //here it the body of the function
    std::unique_ptr<ASTnode> body=std::move(constructCompoundStmt(tokens,index));// tokens[index] is the body of the function
}
module ConstructAST::construct(const std::vector<std::pair<std::string,std::string> > &tokens) {
    module mod;
    int pos=0;
    mod.Node.push_back(constructFunction(tokens,pos));
    return mod;
}