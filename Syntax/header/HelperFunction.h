//
// Created by 赵鲲翔 on 2024/10/23.
//

#ifndef COMPILER_HELPERFUNCTION_H
#define COMPILER_HELPERFUNCTION_H
#include <vector>
#include <string>
#include <utility>
// ExpressionEvaluator.h
#include <string>
#include <vector>
#include <utility>
// 函数声明

// 计算表达式并返回结果和类型
std::pair<double, std::string> evaluateExpression(const std::string& expr);
std::pair<double, std::string> evaluateExpression(const std::vector<std::string>& tokens);
// 辅助函数，用于将中缀表达式转换为后缀表达式
std::vector<std::string > infixToPostfix(const std::vector<std::string>& tokens);
std::vector<std::pair<std::string,std::string> > infixToPostfixs(const std::vector<std::pair<std::string,std::string> >& tokens,int Lindex,int Rindex);

// 辅助函数，用于计算后缀表达式
double evaluatePostfix(const std::vector<std::string>& postfix);

// 分割表达式字符串为单个token
std::vector<std::string> tokenize(const std::string& expr);

// 根据运算符获取优先级
int precedence(const std::string& op);

// 执行运算操作
double applyOp(const std::string& op, double a, double b = 0);


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
std::pair<int ,int> FindCorrspondingPair(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str,std::string str2);
// we need to find the pos of all cetain token,but we need to ignore the token in the bracket
std::vector<int> FindAllExistedIgnoreBracket(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str);
#endif //COMPILER_HELPERFUNCTION_H
