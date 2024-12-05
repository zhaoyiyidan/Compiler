//
// Created by 赵鲲翔 on 2024/10/28.
//

#ifndef COMPILER_SYMBOL_H
#define COMPILER_SYMBOL_H

#include <string>
#include <vector>
#include <limits>
//
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

class Symbol {
    public:
    std::string name;// temporary not use
    std::string type;// the type of this IDEN
    double value=std::numeric_limits<double>::quiet_NaN();// the value of this IDEN
    int memoryLocation;
    std::vector<Symbol> ManySymbol;// it is used to store the symbol of the struct and array

    llvm::Value* llvmValue= nullptr;// the value of  this IDEN in llvm
    llvm::AllocaInst* allocaInst= nullptr;// the allocaInst of this IDEN

    Symbol(const std::string& name, const std::string& type, int memoryLocation) : name(name), type(type), memoryLocation(memoryLocation) {}
    Symbol(const std::string& name, const std::string& type, int memoryLocation, std::vector<Symbol> symbols) : name(name), type(type), memoryLocation(memoryLocation), ManySymbol(symbols) {}
    const std::string& getName() const {
        return name;
    }
    Symbol(const std::string& name, const std::string& type, double value, int memoryLocation) : name(name), type(type), value(value), memoryLocation(memoryLocation) {}
    const std::string& getType() const {
        return type;
    }
    int getMemoryLocation() const {
        return memoryLocation;
    }
    double getValue() const {
        return value;
    }
    // set the value
    void SetValue(double value){
        this->value=value;
    }
};


#endif //COMPILER_SYMBOL_H
