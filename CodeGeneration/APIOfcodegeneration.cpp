//
// Created by 赵鲲翔 on 2024/10/11.
//

#include "APIOfcodegeneration.h"

void generateCode(module &node,std::string path){
    std::string output = path.substr(0, path.find_last_of('.')) ;
    std::string cpppath = output + ".cpp";
    std::string llpath = output + ".ll";
    std::string objectpath = output + ".o";
    IR_Transform ir_transform=IR_Transform("1");
    ir_transform.Precodition(cpppath,path);
    try{
    for(auto &stmt : node.Node){
        stmt->accept(ir_transform);
    }
    saveModuleToFile(ir_transform.llvm_part.module, llpath);
    GenerateObject(llpath,objectpath);
    GenerateExecutable(objectpath,path);
    }
    catch (std::exception &e){
        ir_transform.ExcpetionHandle(cpppath,path);
        std::cout<<"exe";
    }
}
void saveModuleToFile(llvm::Module &M, const std::string &outputFile) {
    std::error_code EC;
    llvm::raw_fd_ostream outputStream(outputFile, EC, llvm::sys::fs::OF_None);
    if (EC) {
        std::cerr << "Error creating output file: " << EC.message() << std::endl;
        return;
    }
    // 将 Module 输出为 .ll 格式
    M.print(outputStream, nullptr);  // nullptr 表示不包含注释
    std::cout << "Module saved to: " << outputFile << std::endl;
}
void GenerateObject(std::string llpath,std::string objpath){
    std::string command = "clang -c " + llpath+ " -o " + objpath;
    int result=std::system(command.c_str());
    if (result==0){
        std::cout<<"Object file generated successfully"<<std::endl;
    } else{
        std::cout<<"Object file generated failed"<<std::endl;
    }

}
void GenerateExecutable(std::string objpath,std::string exepath){
    std::string command = "clang " + objpath+ " -o " + exepath;
    int result=std::system(command.c_str());
    if (result==0){
        std::cout<<"Executable file generated successfully"<<std::endl;
    } else{
        std::cout<<"Executable file generated failed"<<std::endl;
    }
}
void PreCodition(std::string path){
    std::string output = path.substr(0, path.find_last_of('.')) ;
    std::string cpppath = output + ".cpp";
    std::string llpath = output + ".ll";
    std::string objectpath = output + ".o";
    IR_Transform ir_transform=IR_Transform("1");
    ir_transform.Precodition(cpppath,path);
}