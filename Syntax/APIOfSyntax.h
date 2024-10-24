//
// Created by 赵鲲翔 on 2024/10/24.
//

#ifndef COMPILER_APIOFSYNTAX_H
#define COMPILER_APIOFSYNTAX_H

#include <vector>
#include <string>
#include <utility>
#include "header/ConstructAST.h"
module buildASTTree(std::vector<std::pair<std::string,std::string> > tokens);
std::string GetNodeType(const std::unique_ptr<ASTnode> &node);
template <typename NodeType>
NodeType* GetNode(const std::unique_ptr<ASTnode> &node);
#endif //COMPILER_APIOFSYNTAX_H
