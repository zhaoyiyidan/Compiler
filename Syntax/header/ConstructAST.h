//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_CONSTRUCTAST_H
#define COMPILER_CONSTRUCTAST_H
// std
#include <stack>
#include <cctype>
//
#include "module.h"
#include "ASTnode.h"
// the class need to  construct AST
#include "Declaration/FunctionDec.h"
#include "statement/compoundstmt.h"
#include "statement/ReturnStmt.h"
#include "statement/AssignStmt.h"
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
#include "Declaration/ConstDecl.h"
#include "Declaration/VarDecl.h"
#include "Declaration/ConstDef.h"
#include "Declaration/VarDef.h"
#include "Type/IntegerLiteral.h"

#include "statement/IFStmt.h"
#include "statement/WhileStmt.h"
#include "statement/ForStmt.h"

#include "statement/BreakStmt.h"
#include "statement/ContinueStmt.h"
#include "Type/LValue.h"
#include "HelperFunction.h"
#include "statement/EXP.h"

// you can use this class to read and construct a AST
    module ConstructMoule(const std::vector<std::pair<std::string,std::string> > &tokens);// it is the root of the whole AST
    // construct module ,you need  following function
    std::unique_ptr<ASTnode> ConstructFuncDel(const std::vector<std::pair<std::string,std::string> > &tokens,int &index);
    // construct function declaration,you need following function
    std::unique_ptr<ASTnode> ConstructFuncType(std:: string type);
    std::unique_ptr<ASTnode> ConstructCompoundStmt(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructItem(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructItems(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    // stmt
    std::unique_ptr<ASTnode> ConstructStmt(const std::vector<std::pair<std::string,std::string> > &tokens,int &index);
    std::unique_ptr<ASTnode> ConstructReturnStmt(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructAssignStmt(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    //  decl
    std::unique_ptr<ASTnode> ConstructDecl(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructConstDecl(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructConstDef(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructVarDecl(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructVarDef(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    // exp
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
    // end of exp
    // another way to build exp
    std::unique_ptr<ASTnode> ConstructEXP(const std::vector<std::pair<std::string,std::string> >  &tokens);
    // contruct node
    std::unique_ptr<ASTnode> ConstructIFStmt(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructWhileStmt(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructForStmt(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    //
    std::unique_ptr<ASTnode> ConstructBreakStmt(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    std::unique_ptr<ASTnode> ConstructContinueStmt(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
    // here is some helper function







#endif //COMPILER_CONSTRUCTAST_H
