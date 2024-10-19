//
// Created by 赵鲲翔 on 2024/10/14.
//

#ifndef COMPILER_FUNCTIONTYPE_H
#define COMPILER_FUNCTIONTYPE_H

#include "../Type.h"
class FunctionType: public Type {
public:
    std::string type;
    FunctionType(std::string type): type(type){}
    void getNode() override{
        std::cout<<type;
    }
};


#endif //COMPILER_FUNCTIONTYPE_H
