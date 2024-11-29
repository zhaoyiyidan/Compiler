//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_APIOFCODEGENERATION_H
#define COMPILER_APIOFCODEGENERATION_H
#include "IR_Transform.h"
// you can use this function to generate executable file
void generateCode(module &node){
    IR_Transform ir_transform=IR_Transform("1");
    for (auto &node:node.Node){
        node->accept(ir_transform);
    }
    ir_transform.llvm_part.module.print(llvm::outs(), nullptr);
}


#endif //COMPILER_APIOFCODEGENERATION_H
