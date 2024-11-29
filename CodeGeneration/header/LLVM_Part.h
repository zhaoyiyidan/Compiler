//
// Created by 赵鲲翔 on 2024/11/20.
//

#ifndef COMPILER_LLVM_PART_H
#define COMPILER_LLVM_PART_H

#include <llvm/IRBuilder.h>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

#include <llvm/IR/IRBuilder.h>          // 用于生成LLVM IR指令
#include <llvm/IR/LLVMContext.h>        // 用于管理LLVM的全局状态
#include <llvm/IR/Module.h>             // 用于表示一个LLVM模块
#include <llvm/IR/Verifier.h>           // 用于验证生成的IR
#include <llvm/Support/raw_ostream.h>   // 用于输出IR
#include <llvm/Support/TargetSelect.h>  // 用于初始化目标
#include <llvm/Target/TargetMachine.h>  // 用于生成目标机器代码
#include <llvm/Target/TargetOptions.h>  // 用于设置目标选项
#include <llvm/IR/LegacyPassManager.h>  // 用于管理优化和代码生成的Pass
#include <llvm/Support/FileSystem.h>    // 用于文件系统操作
// #include <llvm/Support/Host.h>          // 用于获取主机信息
#include <llvm/Support/CommandLine.h>   // 用于处理命令行参数
#include <llvm/Support/FormattedStream.h> // 用于格式化输出
//
#include "vector"
class LLVM_Part {
public:
    llvm::LLVMContext context;
    llvm::Module module;
    llvm::IRBuilder<> builder;
    llvm::Function *currentFunction;// when not used in the code, set it to nullptr
    std::vector<llvm::BasicBlock*> blockStack;// when not use ,delet all elements
    int pos=-1;
    LLVM_Part(const std::string& name) : module(name, context), builder(context) {}// 创建LLVM上下文和模块
    //  创建一个新的基本块在blockStack的末尾
    void CreateNewBlock(const std::string &name){
        blockStack.push_back(llvm::BasicBlock::Create(context, name, currentFunction));
    }

};


#endif //COMPILER_LLVM_PART_H
