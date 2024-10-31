//
// Created by 赵鲲翔 on 2024/10/23.
//

#ifndef COMPILER_HELPERFUNCTION_H
#define COMPILER_HELPERFUNCTION_H
#include <vector>
#include <string>
#include <utility>

std::pair<bool,int> FindExisted(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str);
std::pair<bool,int> FindLeftExisted(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str);
std::pair<std::string ,int> FindMulExisted(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,const std::vector<std::string> &str);
std::vector<int> FindAllExisted(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str);
std::vector<int> FindPrimary(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str,std::string str2);
//
std::string DeclOrStmt(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
std::string ReturnOrAssign(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
std::string ConstDeclOrVarDecl(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex);
// here is some error function
std::string LackOf(std::string str);
std::pair<bool,int> FindCorrsponding(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str,std::string str2);

#endif //COMPILER_HELPERFUNCTION_H
