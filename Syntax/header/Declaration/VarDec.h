//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_VARDEC_H
#define COMPILER_VARDEC_H
#include "../Declaration.h"
#include "string"
class VarDec: public Declaration {
public:
    std::string name;// this is the name of the variable
    std::unique_ptr<ASTnode> type;// this is the type of the variable // temporary not use
    void getNode() override{

    }
};


#endif //COMPILER_VARDEC_H
