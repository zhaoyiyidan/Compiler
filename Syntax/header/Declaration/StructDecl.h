//
// Created by 赵鲲翔 on 2024/11/14.
//

#ifndef COMPILER_STRUCTDECL_H
#define COMPILER_STRUCTDECL_H

#include "../Declaration.h"

class StructDecl : public Declaration {
public:
    std::string name;
    std::unique_ptr<ASTnode> body;
    StructDecl(std::string name, std::unique_ptr<ASTnode> body) : name(name), body(std::move(body)) {}
    void getNode() override {
        std::cout << "struct  " << name << std::endl<<"{";
        body->getNode();
        std::cout << "}" << std::endl;
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
    std::string GetNodeType() override {
        return "structDecl";
    }
    virtual llvm::Value* codeGen(CodeGenContext& context) override;
};


#endif //COMPILER_STRUCTDECL_H
