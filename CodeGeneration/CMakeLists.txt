add_subdirectory(Test)
add_library(CodeGeneration APIOfcodegeneration.cpp APIOfcodegeneration.h
        A.cpp
        A.h)
##
cmake_minimum_required(VERSION 3.9)
project(Code)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

# 查找LLVM包
find_package(LLVM REQUIRED CONFIG)

# 输出LLVM的版本信息
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# 添加LLVM头文件路径
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# 设置要链接的LLVM库组件
llvm_map_components_to_libnames(llvm_libs core support irreader)

# 添加项目源文件
add_executable(my_project
        A.cpp
)

# 链接LLVM库
target_link_libraries(my_project ${llvm_libs})
target_link_libraries(CodeGeneration ${llvm_libs})
