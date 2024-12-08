#include "Compile.h"
int main(){
    // you need absolute path to use gettoken
    /*
    auto token=gettoken("/Users/zhaokunxiang/clion/compiler/Test/source1.cpp");
    auto tree= buildASTTree(token);// it do not support struct now
    auto sym=analysis(tree);
    tree.getNode();
    */
    compile("/Users/zhaokunxiang/clion/compiler/Test/ForStmt.cpp","/Users/zhaokunxiang/clion/compiler/Test/ForStmt.exe");
        }
