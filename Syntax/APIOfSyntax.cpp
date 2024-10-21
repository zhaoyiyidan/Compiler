//
// Created by 赵鲲翔 on 2024/10/11.
//

#include "APIOfSyntax.h"
#include "Source/ConstructAST.cpp"
// this is the api of the semantic module
// it is used to provide the interface for the other module to use the semantic module
module buildASTTree(std::vector<std::pair<std::string,std::string> > tokens){
    ConstructAST a;
    return a.ConstructMoule(tokens);
}