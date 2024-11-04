//
// Created by 赵鲲翔 on 2024/10/11.
//

#include "APIOfSyntax.h"

// you can use this to build the AST tree
module buildASTTree(std::vector<std::pair<std::string,std::string> > tokens){
    return ConstructMoule(tokens);
}

// not use
// you are expected to combine following two functions to get the node
std::string GetNodeType(const std::unique_ptr<ASTnode> &node){
    return node->GetNodeType();
};
template <typename NodeType>
NodeType* GetNode(const std::unique_ptr<ASTnode> &node){
    return dynamic_cast<NodeType*>(node.get());
}

