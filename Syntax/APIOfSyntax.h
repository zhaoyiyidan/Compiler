//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_APIOFSYNTAX_H
#define COMPILER_APIOFSYNTAX_H

#include "./header/module.h"
#include <vector>
#include <string>
#include <utility>
// you can use this to build the AST tree
module buildASTTree(std::vector<std::pair<std::string,std::string> > tokens);
// you are expected to combine following two functions to get the node
std::string GetNodeType(const std::unique_ptr<ASTnode> &node){
    return node->GetNodeType();
};
template <typename NodeType>
NodeType* GetNode(const std::unique_ptr<ASTnode> &node){
    return dynamic_cast<NodeType*>(node.get());
}
#endif //COMPILER_APIOFSYNTAX_H
