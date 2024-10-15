//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_CONSTRUCTAST_H
#define COMPILER_CONSTRUCTAST_H
#include "module.h"
#include "ASTnode.h"
// you can use this class to read and construct a AST
class ConstructAST {
public:
    module construct(const std::vector<std::pair<std::string,std::string> > &tokens);
    std::unique_ptr<ASTnode> constructFunction(const std::vector<std::pair<std::string,std::string> > &tokens,int &index);// use reference to change the value of index
    std::unique_ptr<ASTnode> constructType(std::string type);
    std::unique_ptr<ASTnode> constructCompoundStmt(const std::vector<std::pair<std::string,std::string> > &tokens,int& index);// use reference to change the value of index
    std::unique_ptr<ASTnode> constructBinary(const std::vector<std::pair<std::string,std::string> > &tokens,int index);
    std::unique_ptr<ASTnode> constructAssign(const std::vector<std::pair<std::string,std::string> > &tokens,int& index);
    std::unique_ptr<ASTnode> constructVarDec(const std::vector<std::pair<std::string,std::string> > &tokens,int& index);
};


#endif //COMPILER_CONSTRUCTAST_H
