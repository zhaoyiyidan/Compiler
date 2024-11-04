//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_FUNCTIONDEC_H
#define COMPILER_FUNCTIONDEC_H

#include "../Declaration.h"
#include "../Type/FunctionType.h"
class FunctionDec: public Declaration {
public:
    std::string NodeType="FunctionDec";
    std::unique_ptr<ASTnode> type;// functiontype
    std::string name;
    std::unique_ptr<ASTnode> body;// this is the body of the function. compoundstmt
    FunctionDec(std::unique_ptr<ASTnode> type, std::string name, std::unique_ptr<ASTnode> body): type(std::move(type)), name(name), body(std::move(body)){};
    void getNode() override {
        if (type)
            type->getNode();
        std::cout<<" "<<name<<"(";
        std::cout<<")";
        if(body)
        body->getNode();
    }
    std::string GetNodeType() override{
        return NodeType;
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};
// node->accept();


#endif //COMPILER_FUNCTIONDEC_H
