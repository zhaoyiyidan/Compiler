add_subdirectory(Test)
# c++ vesrion 17 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_library(Lexical
        APIOfLexical.cpp
        APIOfLexical.h
        tem.cpp
        tem.h
        Test/a.cpp
)