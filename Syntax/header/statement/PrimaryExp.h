//
// Created by 赵鲲翔 on 2024/10/15.
//

#ifndef COMPILER_PRIMARYEXP_H
#define COMPILER_PRIMARYEXP_H

#include "../statement.h"
class PrimaryExp : public statement{
public:
    std::unique_ptr<ASTnode> expression;// "(", Exp, ")" or Number
    std::string str;
    void getNode() override{
        if (expression)
        expression->getNode();
    }
};


#endif //COMPILER_PRIMARYEXP_H
