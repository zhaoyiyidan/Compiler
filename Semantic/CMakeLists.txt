# c++ version is 17
cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(Test)
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
)





