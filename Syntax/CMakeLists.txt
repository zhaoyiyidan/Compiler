set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
##
add_subdirectory(Test)
file(GLOB_RECURSE SOURCE_FILES "Source/*.cpp")
file(GLOB_RECURSE HEADER_FILES "header/*.h")
add_executable(Tem  tem.cpp
        ${SOURCE_FILES}
        )
add_library(ASTNode
        ${SOURCE_FILES} ${HEADER_FILES} APIOfSyntax.cpp APIOfSyntax.h
)