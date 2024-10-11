//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_DECLARATION_H
#define COMPILER_DECLARATION_H


class Declaration {
public:
    // search algorithm
    // this function is used to search the tree depending on the order you want to iterate
    // you can search in pre in post order
    virtual std::vector<std::string> searchDel(std::string order);
};


#endif //COMPILER_DECLARATION_H
