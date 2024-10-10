
cmake_minimum_required(VERSION 3.9)
project(Compiler)

# Enable testing functionality in CMake
enable_testing()
# 添加 Google Test
add_subdirectory(Library/googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# 添加项目的子目录
add_subdirectory(CodeGeneration)
add_subdirectory(Lexical)
add_subdirectory(Semantic)
add_subdirectory(Syntax)
#添加执行文件
add_executable(Compiler main.cpp)

