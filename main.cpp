#include "iostream"
#include "Syntax/APIOfSyntax.h"
#include "Lexical/APIOfLexical.h"
 #include "Semantic/APIOfSemantic.h"
int main(){
    // you need absolute path to use gettoken
    auto token=gettoken("/Users/atri/CLionProjects/Compiler/Test/struct.cpp");
    auto tree= buildASTTree(token);// it do not support struct now
    auto sym=analysis(tree);
    tree.getNode();
        }
