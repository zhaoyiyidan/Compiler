
cmake_minimum_required(VERSION 3.10)
# C++ version
set(CMAKE_CXX_STANDARD 17)
project(Compiler)
# Enable testing functionality in CMake
enable_testing()
# 添加 Google Test
add_subdirectory(Library/googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# 添加项目的子目录
add_subdirectory(CodeGeneration)
add_subdirectory(Lexical)
add_subdirectory(Syntax)
add_subdirectory(Semantic)
#添加执行文件
add_executable(Compiler main.cpp
        Compile.cpp
        Compile.h
)
# 添加链接库
target_link_libraries(Compiler PRIVATE ASTNode CodeGeneration Lexical  Semantic)

find_package(LLVM REQUIRED CONFIG)
target_link_libraries(Compiler PRIVATE LLVM)
target_include_directories(Compiler PRIVATE ${LLVM_INCLUDE_DIRS})

