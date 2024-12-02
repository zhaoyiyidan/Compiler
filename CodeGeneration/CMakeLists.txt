cmake_minimum_required(VERSION 3.10)
project(Code)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

# 查找LLVM
find_package(LLVM REQUIRED CONFIG)

# 打印调试信息，查看CMake是否找到了LLVM
message(STATUS "LLVM_INCLUDE_DIRS: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM_LIBRARY_DIRS: ${LLVM_LIBRARY_DIRS}")
message(STATUS "LLVM_VERSION: ${LLVM_VERSION_STRING}")

# 添加LLVM头文件路径到目标
add_library(CodeGeneration
        APIOfcodegeneration.cpp
        APIOfcodegeneration.h
        A.cpp
        A.h
        IR_Transform.cpp
        IR_Transform.h
        Source/LLVM_Part.cpp
        header/LLVM_Part.h
        HelperFunction.cpp
        HelperFunction.h
        header/BlockTree.h
        INT.h
)

target_link_libraries(CodeGeneration PRIVATE LLVM)
target_include_directories(CodeGeneration PRIVATE ${LLVM_INCLUDE_DIRS}) #



