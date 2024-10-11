//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_APIOFSEMANTIC_H
#define COMPILER_APIOFSEMANTIC_H

#include "./header /module.h"
#include <vector>
#include <string>
#include <utility>
// you can use this to built the AST tree
module buildASTTree(std::vector<std::pair<std::string,std::string> > tokens);
// you can get the whole AST tree by calling this function
module getASTTree();
// you can iterate the AST tree by calling this function
void iterateASTTree(module node);

#endif //COMPILER_APIOFSEMANTIC_H
