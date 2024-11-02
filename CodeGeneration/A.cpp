//
// Created by 赵鲲翔 on 2024/11/2.
//

#include "A.h"
//
// Created by 赵鲲翔 on 2024/11/2.
//

// src/test_llvm.cpp
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

int main() {
    // 创建LLVM上下文和模块
    llvm::LLVMContext context;
    llvm::Module module("test_module", context);
    llvm::IRBuilder<> builder(context);

    // 创建一个返回整型的函数
    llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getInt32Ty(), false);
    llvm::Function *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);

    // 创建一个基本块，并将IRBuilder的插入点设置为基本块的开头
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(entry);

    // 创建返回指令，返回值为0
    builder.CreateRet(builder.getInt32(0));

    // 验证生成的IR模块
    if (llvm::verifyModule(module, &llvm::errs())) {
        llvm::errs() << "Error: Module verification failed!\n";
        return 1;
    }

    // 输出生成的IR
    module.print(llvm::outs(), nullptr);

    return 0;
}
