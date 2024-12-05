# c++ version is 17
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(Test)
find_package(LLVM REQUIRED CONFIG)

add_library(Semantic
        Source/AnalysisAST.cpp
        header/AnalysisAST.h
        Source/SymbolTable.cpp
        header/SymbolTable.h
        Source/Symbol.cpp
        header/Symbol.h
        Source/Scope.cpp
        header/Scope.h
        Analysis.cpp
        Analysis.h
        APIOfSemantic.cpp
        APIOfSemantic.h
)
target_link_libraries(Semantic PRIVATE LLVM)
target_include_directories(Semantic PRIVATE ${LLVM_INCLUDE_DIRS}) #





