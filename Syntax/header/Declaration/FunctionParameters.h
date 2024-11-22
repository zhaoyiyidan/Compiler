//
// Created by 赵鲲翔 on 2024/11/4.
//

#ifndef COMPILER_FUNCTIONPARAMETERS_H
#define COMPILER_FUNCTIONPARAMETERS_H

#include "../Declaration.h"
// not used
class FunctionParameters :public Declaration{
public:
    std::unique_ptr<ASTnode> type;
    std::string IDEN;
    FunctionParameters(std::unique_ptr<ASTnode> type, std::string IDEN):type(std::move(type)),IDEN(std::move(IDEN)){}
    void getNode() override{
        if (type)
            type->getNode();
        std::cout<<" "<<IDEN;
    }
    std::string GetNodeType() override{
        return "FunctionParameters";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
    virtual llvm::Value* codeGen(CodeGenContext& context) override;
};


#endif //COMPILER_FUNCTIONPARAMETERS_H
