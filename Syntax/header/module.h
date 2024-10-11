//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_MODULE_H
#define COMPILER_MODULE_H
// this file needed
#include "vector"
#include "Declaration.h"
#include "statement.h"
#include "Type.h"
#include <string>
// this is a module, it is the root of the AST
// it contains all the other classes

class module {
public:
    std::vector<Declaration*> del;// 1
    std::vector<statement*> stmt;// 2
    std::vector<Type*> type;// 3
    std::vector<int> iterateOrder;// if it contains 1,you need to iterate the del,if it contains 2,you need to iterate the stmt,if it contains 3,you need to iterate the type
    // this is the constructor,need to be implemented
    module();
    // search algorithm
    // this function is used to search the tree depending on the order you want to iterate
    // you can search in pre in post order
    std::vector<std::string> search(std::string order);

};


#endif //COMPILER_MODULE_H
