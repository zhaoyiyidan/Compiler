//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_CONSTRUCTAST_H
#define COMPILER_CONSTRUCTAST_H
#include "module.h"
#include "ASTnode.h"
// the class need to  construct AST
#include "Declaration/FunctionDec.h"
#include "statement/compoundstmt.h"
#include "statement/Stmt.h"
#include "statement/Expression.h"
#include "statement/LOrExp.h"
#include "statement/LAndExp.h"
#include "statement/EqExp.h"
#include "statement/RelExp.h"
#include "statement/AddExp.h"
#include "statement/MulExp.h"
#include "statement/UnaryExp.h"
#include "statement/PrimaryExp.h"
#include "statement/UnaryOp.h"

// you can use this class to read and construct a AST
class ConstructAST {
public:
    module ConstructMoule(const std::vector<std::pair<std::string,std::string> > &tokens);// it is the root of the whole AST
    // construct module ,you need  following function
    std::unique_ptr<ASTnode> ConstructFuncDel(const std::vector<std::pair<std::string,std::string> > &tokens,int &index);
    // construct function declaration,you need following function
    std::unique_ptr<ASTnode> ConstructFuncType(std:: string type);
    std::unique_ptr<ASTnode> ConstructCompoundStmt(const std::vector<std::pair<std::string,std::string> > &tokens,int &index);
    std::unique_ptr<ASTnode> ConstructStmt(const std::vector<std::pair<std::string,std::string> > &tokens,int &index);
    std::unique_ptr<ASTnode> ConstructExp(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructLOrExp(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructLAndExp(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructEqExp(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructRelExp(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructAddExp(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructMulExp(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructUnaryExp(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructPrimaryExp(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructUnaryOp(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);

    // here is some helper function
    std::pair<bool,int> FindExisted(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str);
    std::pair<bool,int> FindLeftExisted(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str);
    std::pair<std::string ,int> FindMulExisted(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,const std::vector<std::string> &str);
    bool ExistPrimaryOrUnaryOp(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    bool ExistUnaryOp(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    bool ExistPrimary(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    // here is some error function
    std::string LackOf(std::string str);

};


#endif //COMPILER_CONSTRUCTAST_H
