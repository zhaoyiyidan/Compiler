//
// Created by 赵鲲翔 on 2024/10/14.
//

#ifndef COMPILER_FUNCTIONTYPE_H
#define COMPILER_FUNCTIONTYPE_H

#include "../Type.h"
class FunctionType: public Type {
public:
    std::string type="int";
    FunctionType(std::string type): type(type){}
};


#endif //COMPILER_FUNCTIONTYPE_H
