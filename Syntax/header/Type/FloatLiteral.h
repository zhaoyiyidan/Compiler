//
// Created by 赵鲲翔 on 2024/10/14.
//
// not use
#ifndef COMPILER_FLOATLITERAL_H
#define COMPILER_FLOATLITERAL_H

#include <iostream>
class FloatLiteral {
public:
    float value;
    FloatLiteral(float value): value(value){}
    void getNode()  {

    }
    std::string GetNodeType() {
        return "FloatLiteral";
    }
    virtual llvm::Value* codeGen(CodeGenContext& context) override;

};


#endif //COMPILER_FLOATLITERAL_H
