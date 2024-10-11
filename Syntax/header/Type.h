//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_TYPE_H
#define COMPILER_TYPE_H


class Type {
public:
    // search algorithm
    // this function is used to search the tree depending on the order you want to iterate
    // you can search in pre in post order
    virtual std::vector<std::string> searchType(std::string order);

};


#endif //COMPILER_TYPE_H
