//
// Created by 赵鲲翔 on 2024/10/31.
//

#ifndef COMPILER_CONTINUESTMT_H
#define COMPILER_CONTINUESTMT_H

#include "../statement.h"
class ContinueStmt: public statement {
public:
    std::string GetNodeType() override {
        return "ContinueStmt" ;
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
    void getNode() override {
        std::cout << "continue;" << std::endl;
    }
    ContinueStmt() = default;
};


#endif //COMPILER_CONTINUESTMT_H
