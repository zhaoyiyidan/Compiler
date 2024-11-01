//
// Created by 赵鲲翔 on 2024/11/1.
//

#ifndef COMPILER_EXP_H
#define COMPILER_EXP_H

#include "../statement.h"
class EXP: public statement {
public:
    std::unique_ptr<ASTnode> Left;
    std::string value;
    std::unique_ptr<ASTnode> Right;
    EXP(std::unique_ptr<ASTnode> Left,std::string value,std::unique_ptr<ASTnode> Right):Left(std::move(Left)),value(value),Right(std::move(Right)){}
    EXP(std::string value):value(value){Left=nullptr;Right=nullptr;}
    void getNode() override{
        if (Left){
            std::cout<<std::endl;
        Left->getNode();
        }
        std::cout<<value;
        if (Right){
            std::cout<<std::endl;
        Right->getNode();
        }
    }
    std::string GetNodeType() override{
        return "EXP";
    }
    void accept(VistorAST &vistor) override{
        vistor.visit(*this);
    }
};


#endif //COMPILER_EXP_H
