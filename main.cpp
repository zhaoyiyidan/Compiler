#include "iostream"
#include "Syntax/APIOfSyntax.h"
#include "Lexical/APIOfLexical.h"
#include "Semantic/APIOfSemantic.h"
int main(){
    // you need absolute path to use gettoken
    auto token=gettoken("/Users/zhaokunxiang/clion/compiler/Test/source1.cpp");
    auto tree= buildASTTree(token);
    auto sym=analysis(tree);
    tree.getNode();
}