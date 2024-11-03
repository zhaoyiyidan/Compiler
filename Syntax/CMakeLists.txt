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
        VistorAST.cpp
        VistorAST.h
        Source/IFStmt.cpp
        header/statement/IFStmt.h
        Source/WhileStmt.cpp
        header/statement/WhileStmt.h
        Source/ForStmt.cpp
        header/statement/ForStmt.h
        Source/LValue.cpp
        header/Type/LValue.h
        Source/BreakStmt.cpp
        header/statement/BreakStmt.h
        Source/ContinueStmt.cpp
        header/statement/ContinueStmt.h
        Source/statement/EXP.cpp
        header/statement/EXP.h
)
target_include_directories(ASTNode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header)