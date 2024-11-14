//
// Created by 赵鲲翔 on 2024/11/14.
//

#ifndef COMPILER_STRUCTBODY_H
#define COMPILER_STRUCTBODY_H

#include "../Declaration.h"
class StructBody : public Declaration {
public:
    std::vector<std::unique_ptr<ASTnode>> body;
    StructBody(std::vector<std::unique_ptr<ASTnode>> body) : body(std::move(body)) {}
    void getNode() override {
        for (auto &i : body) {
            i->getNode();
        }
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
    std::string GetNodeType() override {
        return "structBody";
    }
};


#endif //COMPILER_STRUCTBODY_H
