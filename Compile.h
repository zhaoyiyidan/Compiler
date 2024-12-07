//
// Created by 赵鲲翔 on 2024/11/29.
//

#ifndef COMPILER_COMPILE_H
#define COMPILER_COMPILE_H

#include "iostream"
#include "Syntax/APIOfSyntax.h"
#include "Lexical/APIOfLexical.h"
 #include "CodeGeneration/APIOfcodegeneration.h"
void compile(std::string filename,std::string path){
    auto tokens= gettoken(filename);
    auto tree= buildASTTree(tokens);//
    generateCode(tree,path);
}

#endif //COMPILER_COMPILE_H
