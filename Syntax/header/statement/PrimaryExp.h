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
    std::string GetNodeType() override{
        return "PrimaryExp";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_PRIMARYEXP_H
