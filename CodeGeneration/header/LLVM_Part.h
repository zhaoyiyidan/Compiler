//
// Created by 赵鲲翔 on 2024/11/20.
//

#ifndef COMPILER_LLVM_PART_H
#define COMPILER_LLVM_PART_H

#include <llvm/IR/IRBuilder.h>
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
#include <vector>
#include <deque>
#include "BlockTree.h"
class LLVM_Part {
public:
    llvm::LLVMContext context;
    llvm::Module module;
    llvm::IRBuilder<> builder;
    llvm::Function *currentFunction;// when not used in the code, set it to nullptr

    std::shared_ptr<BlockTree> root;
    std::shared_ptr<BlockTree> current;// 每次更改current 时，tem也要更改
    // use smart pointer to manage the memory
    llvm::BasicBlock* tem;//
    LLVM_Part(const std::string& name) : module(name, context), builder(context) {

    }// 创建LLVM上下文和模块

    // create a new basic block,it  will change current block
    void CreateNewBlock(const std::string &name){
        if (currentFunction){
            auto block=llvm::BasicBlock::Create(context,name,currentFunction);
            auto tree=std::make_shared<BlockTree>(name,block);
            if (root){ // if it is initailized
            auto mid=std::make_shared<BlockTree>(name);
            mid->SetTree(tree);
            current->child.push_back(mid);
            current=mid;
            }
            else{
                root=std::make_shared<BlockTree>(name);
                current=root;
                current->SetTree(tree);
            }
        }
    }
    void SetCurrentRoot(std::shared_ptr<BlockTree> tree){
        current=tree;
        tem=current->block;
    }
};


#endif //COMPILER_LLVM_PART_H
