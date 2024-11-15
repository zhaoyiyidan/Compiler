//
// Created by 赵鲲翔 on 2024/10/23.
#include "../header/HelperFunction.h"
#include <stack>
#include <sstream>
#include <cctype>
#include <stdexcept>
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

std::string DeclOrStmt(const std::vector<std::pair<std::string, std::string>> &tokens, int Lindex, int Rindex) {
    //
    if (tokens[Lindex].second=="const"){
        return "ConstDecl";
    }
    // temporary solution
    if (tokens[Lindex].first=="KeyWord"&&tokens[Lindex+1].first=="IDEN"){
        return "VarDecl";
    }
    if(tokens[Lindex].second=="return"){
        return "ReturnStmt";
    }
    if (tokens[Lindex].first=="IDEN"&&tokens[Lindex+1].second=="="){
        return "AssignStmt";
    }
    if (tokens[Lindex].first=="NUM"){
        return "EXP";
    }
    if (tokens[Lindex].second=="if"){
        return "IfStmt";
    }
    if (tokens[Lindex].first=="IDEN"&&(tokens[Lindex+1].second=="++")){
        return "increment";
    }
    if (tokens[Lindex].first=="IDEN"&&(tokens[Lindex+1].second=="--")){
        return "decrement";
    }
    if (tokens[Lindex].second=="break"){
        return "break";
    }
    if (tokens[Lindex].second=="continue"){
        return "continue";
    }
    return "null";

}
// here is the implementation of error function
std::string LackOf(std::string str) {
    return str;
}
std::vector<int> FindPrimary(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str,std::string str2) {
    std::vector<int> res;
    int a=0,b=0,c=0;
    for(int i=Lindex;i<Rindex+1;i++){
        if(tokens[i].second==str){
            a++;
        }
        if(tokens[i].second==str2){
            b++;
        }
        if (a==b&&a!=0){
            res.push_back(i);
            a=0;
            b=0;
            c=0;
        }
        if (a==1&&c==0) {
            c=1;
            res.push_back(i);
        }
    }
    return res;

}
std::pair<bool,int> FindCorrsponding(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str,std::string str2) {
    int a=0,b=0;
    for(int i=Lindex;i<Rindex+1;i++){
        if(tokens[i].second==str){
            a++;
        }
        if(tokens[i].second==str2){
            b++;
        }
        if (a==b&&a!=0){
            return std::make_pair(true,i);
        }
    }
    return std::make_pair(false,-1);
}
std::pair<int ,int> FindCorrspondingPair(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str,std::string str2) {
    int a=0,b=0;
    for(int i=Lindex;i<Rindex+1;i++){
        if(tokens[i].second==str){
            a++;
        }
        if(tokens[i].second==str2){
            b++;
        }
        if (a==b&&a!=0){
            return std::make_pair(a,b);
        }
    }
    return std::make_pair(-1,-1);
}

// 获取操作符优先级
int precedence(const std::string& op) {
    if (op == "||") return 1;
    if (op == "&&") return 2;
    if (op == ">" || op == "<" || op == ">=" || op == "<=" || op == "==" || op == "!=") return 3;
    if (op == "+" || op == "-") return 4;
    if (op == "*" || op == "/" || op == "%") return 5;
    if (op == "!") return 6;
    return 0;
}

// 执行运算
double applyOp(const std::string& op, double a, double b) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return a / b;
    if (op == "%") return static_cast<int>(a) % static_cast<int>(b);
    if (op == "&&") return static_cast<bool>(a) && static_cast<bool>(b);
    if (op == "||") return static_cast<bool>(a) || static_cast<bool>(b);
    if (op == ">") return a > b;
    if (op == "<") return a < b;
    if (op == ">=") return a >= b;
    if (op == "<=") return a <= b;
    if (op == "==") return a == b;
    if (op == "!=") return a != b;
    if (op == "!") return !static_cast<bool>(a);
    throw std::runtime_error("Unknown operator");
}

// 中缀表达式转换为后缀表达式
std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens) {
    std::stack<std::string> ops;
    std::vector<std::string> postfix;
    for (const auto& token : tokens) {
        if (isdigit(token[0]) || token == "true" || token == "false" || (token.size() == 1 && isalpha(token[0]))) {
            postfix.push_back(token);
        } else if (token == "(") {
            ops.push(token);
        } else if (token == ")") {
            while (!ops.empty() && ops.top() != "(") {
                postfix.push_back(ops.top());
                ops.pop();
            }
            ops.pop();
        } else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                postfix.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
    }
    while (!ops.empty()) {
        postfix.push_back(ops.top());
        ops.pop();
    }
    return postfix;
}
std::vector<std::pair<std::string,std::string> > infixToPostfixs(const std::vector<std::pair<std::string,std::string> >& tokens, int Lindex ,int Rindex) {
    std::stack<std::pair<std::string,std::string> > ops;
    std::vector<std::pair<std::string,std::string> > postfix;
    for (int i=Lindex;i<Rindex+1;i++){
        auto token=tokens[i];
        if (token.first=="IDEN"){
            postfix.push_back({"IDEN",token.second});
        }
        else if (isdigit(token.second[0]) || token.second == "true" || token.second == "false" || (token.second.size() == 1 && isalpha(token.second[0]))) {
            postfix.push_back({token.first,token.second});
        }
        else if (token.second == "(") {
            ops.push({token.first,token.second});
        }
        else if (token.second == ")") {
            while (!ops.empty() && ops.top().second != "(") {
                postfix.push_back(ops.top());
                ops.pop();
            }
            ops.pop();
        }
        else {
            while (!ops.empty() && precedence(ops.top().second) >= precedence(token.second)) {
                postfix.push_back(ops.top());
                ops.pop();
            }
            ops.push({token.first,token.second});
        }
    }
    while (!ops.empty()) {
        postfix.push_back(ops.top());
        ops.pop();
    }
    return postfix;
}

// 计算后缀表达式
double evaluatePostfix(const std::vector<std::string>& postfix) {
    std::stack<double> values;
    for (const auto& token : postfix) {
        if (isdigit(token[0])) {
            values.push(std::stod(token));
        } else if (token == "true") {
            values.push(1);
        } else if (token == "false") {
            values.push(0);
        } else if (token.size() == 1 && isalpha(token[0])) {
            values.push(static_cast<double>(token[0]));
        } else if (token == "!") {
            double a = values.top(); values.pop();
            values.push(applyOp(token, a));
        } else {
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            values.push(applyOp(token, a, b));
        }
    }
    return values.top();
}

// 将字符串分割为tokens
std::vector<std::string> tokenize(const std::string& expr) {
    std::vector<std::string> tokens;
    std::stringstream ss;
    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];
        if (isspace(ch)) continue;
        if (isdigit(ch) || ch == '.') {
            ss << ch;
        } else {
            if (!ss.str().empty()) {
                tokens.push_back(ss.str());
                ss.str("");
            }
            if (ch == '(' || ch == ')') {
                tokens.push_back(std::string(1, ch));
            } else if (ch == '!' && (i == 0 || expr[i-1] == '(')) {
                tokens.push_back("!");
            } else if (ch == '&' || ch == '|') {
                if (expr[i + 1] == ch) {
                    tokens.push_back(std::string(2, ch));
                    i++;
                }
            } else if (ch == '>' || ch == '<' || ch == '=' || ch == '!') {
                if (expr[i + 1] == '=') {
                    tokens.push_back(std::string(1, ch) + "=");
                    i++;
                } else {
                    tokens.push_back(std::string(1, ch));
                }
            } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
                tokens.push_back(std::string(1, ch));
            } else if (expr.substr(i, 4) == "true") {
                tokens.push_back("true");
                i += 3;
            } else if (expr.substr(i, 5) == "false") {
                tokens.push_back("false");
                i += 4;
            } else if (ch == '\'' && i + 2 < expr.length() && expr[i + 2] == '\'') {
                tokens.push_back(std::string(1, expr[i + 1]));
                i += 2;
            }
        }
    }
    if (!ss.str().empty()) tokens.push_back(ss.str());
    return tokens;
}

// 计算表达式并返回结果和类型
std::pair<double, std::string> evaluateExpression(const std::vector<std::string>& tokens) {
    std::vector<std::string> postfix = infixToPostfix(tokens);
    double result = evaluatePostfix(postfix);
    // 判断结果类型
    std::string type;
    bool hasLogicalOrRelationalOperator = false;
    bool containsCharacter = false;

    for (const auto& token : tokens) {
        if (token == "==" || token == "!=" || token == "<" || token == ">" || token == "<=" || token == ">=" || token == "&&" || token == "||") {
            hasLogicalOrRelationalOperator = true;
        }
        if (token.size() == 1 && isalpha(token[0]) && token != "true" && token != "false") {
            containsCharacter = true;
        }
    }

    if (hasLogicalOrRelationalOperator) {
        type = "bool";
    } else if (static_cast<int>(result) == result) {
        if (containsCharacter && result >= 0 && result <= 255) {
            type = "char";
        } else {
            type = "int";
        }
    } else {
        type = "double";
    }
    return std::make_pair(result, type);
}
std::pair<double, std::string> evaluateExpression(const std::string& expr) {
    auto tokens = tokenize(expr);
    std::vector<std::string> postfix = infixToPostfix(tokens);
    double result = evaluatePostfix(postfix);

    // 判断结果类型
    std::string type;
    bool hasLogicalOrRelationalOperator = false;
    bool containsCharacter = false;

    for (const auto& token : tokens) {
        if (token == "==" || token == "!=" || token == "<" || token == ">" || token == "<=" || token == ">=" || token == "&&" || token == "||") {
            hasLogicalOrRelationalOperator = true;
        }
        if (token.size() == 1 && isalpha(token[0]) && token != "true" && token != "false") {
            containsCharacter = true;
        }
    }

    if (hasLogicalOrRelationalOperator) {
        type = "bool";
    } else if (static_cast<int>(result) == result) {
        if (containsCharacter && result >= 0 && result <= 255) {
            type = "char";
        } else {
            type = "int";
        }
    } else {
        type = "double";
    }
    return std::make_pair(result, type);
}
// we need to find the pos of all cetain token,but we need to ignore the token in the bracket
std::vector<int> FindAllExistedIgnoreBracket(const std::vector<std::pair<std::string,std::string> > &tokens,int Lindex,int Rindex,std::string str) {
    std::vector<int> a;
    int bracket=0;
    for(int i=Lindex;i<Rindex+1;i++){
        if(tokens[i].second=="{"){
            bracket++;
        }
        if(tokens[i].second=="}"){
            bracket--;
        }
        if(tokens[i].second==str&&bracket==0){
            a.push_back(i);
        }
    }
    return a;
}


