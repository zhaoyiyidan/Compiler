//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_ASSIGNSTMT_H
#define COMPILER_ASSIGNSTMT_H

#include "../statement.h"
#include "../Declaration/VarDec.h"
#include "expression.h"
class AssignStmt : public statement {
public:
    VarDec* var;
    expression* exp;
};


#endif //COMPILER_ASSIGNSTMT_H
