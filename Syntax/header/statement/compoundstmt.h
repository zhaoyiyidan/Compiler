//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_COMPOUNDSTMT_H
#define COMPILER_COMPOUNDSTMT_H

#include "../statement.h"
// use this to represent the set of a statement,view it as a body of a function
class compoundstmt: public statement {
public:
    std::vector<std::unique_ptr<ASTnode> >  stmts;//the stmt can be a Decl or a statement
    compoundstmt(std::vector<std::unique_ptr<ASTnode> > stmts):stmts(std::move(stmts)){}
    void getNode() override{
        std::cout<<"{"<<" "<<std::endl;
        for (auto &stmt : stmts) {
            if (stmt)
            stmt->getNode();
        }
        std::cout<<std::endl<<"}"<<" "<<std::endl;
    }
    std::string GetNodeType() override{
        return "compoundstmt";
    }
    void accept(VistorAST &vistor) override {
        vistor.visit(*this);
    }
};


#endif //COMPILER_COMPOUNDSTMT_H
