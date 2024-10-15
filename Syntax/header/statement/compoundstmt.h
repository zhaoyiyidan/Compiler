//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_COMPOUNDSTMT_H
#define COMPILER_COMPOUNDSTMT_H

#include "../statement.h"
// i use this to represent the set of a statement,view it as a body of a function
class compoundstmt: public statement {
public:
    std::vector<std::unique_ptr<ASTnode> > stmts;// this is a vector of statements,it is either a Decl or a stmt
};


#endif //COMPILER_COMPOUNDSTMT_H
