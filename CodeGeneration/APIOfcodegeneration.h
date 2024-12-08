//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_APIOFCODEGENERATION_H
#define COMPILER_APIOFCODEGENERATION_H
#include "IR_Transform.h"
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Support/TargetSelect.h>
#include <iostream>
#include <string>
#include <cstdlib>
// you can use this function to generate executable file
void generateCode(module &node,std::string path);
void generatecode(module &node,std::string path);
void saveModuleToFile(llvm::Module &M, const std::string &outputFile);
void GenerateObject(std::string llpath,std::string objpath);
void GenerateExecutable(std::string objpath,std::string exepath);
void PreCodition(std::string path);
#endif //COMPILER_APIOFCODEGENERATION_H
