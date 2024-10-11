add_subdirectory(Test)
add_library(ASTNode
        Source/Type.cpp
        "header /Type.h"
        Source/Declaration.cpp
        "header /Declaration.h"
        Source/statement.cpp
        "header /statement.h"
        "Source/Type/TypedefDecl.cpp"
        "header /Type/TypedefDecl.h"
        Source/Declaration/FunctionDec.cpp
        "header /Declaration/FunctionDec.h"
        Source/statement/compoundstmt.cpp
        "header /statement/compoundstmt.h"
        "Source/module.cpp"
        "header /module.h"
        "Source/Declaration/VarDec.cpp"
        "header /Declaration/VarDec.h"
        "Source/statement/AssignStmt.cpp"
        "header /statement/AssignStmt.h"
        "Source/statement/BinaryOperator.cpp"
        "header /statement/BinaryOperator.h"
        "Source/statement/expression.cpp"
        "header /statement/expression.h"
        "Source/statement/singlestmt.cpp"
        "header /statement/singlestmt.h"
        "Source/Type/Constvalue.cpp"
        "header /Type/Constvalue.h"
        APIOfSemantic.cpp
        APIOfSemantic.h

)