//
// Created by 赵鲲翔 on 2024/12/1.
//

#ifndef COMPILER_BLOCKTREE_H
#define COMPILER_BLOCKTREE_H

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

#include <vector>
#include <string>
// i want to create a tree with llvm::basicBlock as node
// use smart pointer to manage the memory
class BlockTree {
public:
    llvm::BasicBlock* block;
    std::vector<std::shared_ptr<BlockTree> > child;
    std::vector<double> condition;
    llvm::Value* ValueCondition= nullptr;

    std::string name;
    std::shared_ptr<BlockTree> FindLeftMostLeaf(std::shared_ptr<BlockTree> node) {
        if (node == nullptr) return nullptr; // 如果节点为空，返回空
        // 如果当前节点没有子节点，说明它是叶节点
        if (node->child.empty()) {
            return node; // 返回当前节点（叶节点）
        }
        // 递归查找最左子节点
        return FindLeftMostLeaf(node->child[0]); // 总是优先遍历第一个子节点
    }
    std::shared_ptr<BlockTree> FindLeftMostLeaf1(std::shared_ptr<BlockTree> node) {
        if (node == nullptr) return nullptr; // 如果节点为空，返回空
        // 如果当前节点没有子节点，说明它是叶节点
        if (node->child[0]->child.empty()) {
            return node;
        }
        // 递归查找最左子节点
        return FindLeftMostLeaf(node->child[0]); // 总是优先遍历第一个子节点
    }

    std::shared_ptr<BlockTree> FindRightMostLeaf(std::shared_ptr<BlockTree> node) {
        if (node == nullptr) return nullptr; // 如果节点为空，返回空
        // 如果当前节点没有子节点，说明它是叶节点
        if (node->child.empty()) {
            return node; // 返回当前节点（叶节点）
        }
        // 递归查找最右子节点
        return FindRightMostLeaf(node->child.back()); // 总是优先遍历最后一个子节点
    }
    std::shared_ptr<BlockTree> FindRightMostLeaf1(std::shared_ptr<BlockTree> node) {
        if (node == nullptr) return nullptr; // 如果节点为空，返回空
        // 如果当前节点没有子节点，说明它是叶节点
        if (node->child.back()->child.empty()) {
            return node;
        }
        // 递归查找最右子节点
        return FindRightMostLeaf(node->child.back()); // 总是优先遍历最后一个子节点
    }
    BlockTree(const std::string  &str, llvm::BasicBlock* theblock){
        name=str;
        block=theblock;
    }
    BlockTree(const std::string &str){
        name=str;
    }
    // set the tree in the child
    void SetTree(std::shared_ptr<BlockTree> tree ){
        if (tree){
        child.push_back(tree);}
        else{
            std::runtime_error("the tree is nullptr");
        }
    }
};


#endif //COMPILER_BLOCKTREE_H
