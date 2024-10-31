//
// Created by 赵鲲翔 on 2024/10/31.
//

#ifndef COMPILER_BREAKSTMT_H
#define COMPILER_BREAKSTMT_H

#include "../statement.h"
class BreakStmt: public statement {
public:
    std::string GetNodeType() override {
        return "BreakStmt" ;
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
    void getNode() override {
        std::cout << "BreakStmt" << std::endl;
    }

};


#endif //COMPILER_BREAKSTMT_H
