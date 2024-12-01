//
// Created by 赵鲲翔 on 2024/11/29.
//

#ifndef COMPILER_COMPILE_H
#define COMPILER_COMPILE_H

#include "iostream"
#include "Syntax/APIOfSyntax.h"
#include "Lexical/APIOfLexical.h"
 #include "CodeGeneration/APIOfcodegeneration.h"
void compile(std::string name){
    auto tokens= gettoken(name);
    auto tree= buildASTTree(tokens);//
    // auto sym=analysis(tree);
    // tree.getNode();
    generateCode(tree);
}


#endif //COMPILER_COMPILE_H
