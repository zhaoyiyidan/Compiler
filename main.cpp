#include "iostream"
#include "Syntax/APIOfSyntax.h"
#include "Lexical/APIOfLexical.h"
#include "Semantic/APIOfSemantic.h"
int main(){
    auto token=gettoken("/Users/zhaokunxiang/clion/compiler/a.cpp");
    auto tree= buildASTTree(token);
    auto sym=analysis(tree);
    int a=1;
    tree.getNode();
}