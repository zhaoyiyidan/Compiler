//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_VARDEC_H
#define COMPILER_VARDEC_H
#include "../Declaration.h"
#include "string"
class VarDec: public Declaration {
public:
    std::string name;
};


#endif //COMPILER_VARDEC_H
