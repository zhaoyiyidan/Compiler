add_subdirectory(Test)
add_library(Semantic APIOfSemantic.cpp APIOfSemantic.h
        Source/AnalysisAST.cpp
        header/AnalysisAST.h
        Source/SymbolTable.cpp
        header/SymbolTable.h
        Source/Symbol.cpp
        header/Symbol.h
        Source/Scope.cpp
        header/Scope.h
)
