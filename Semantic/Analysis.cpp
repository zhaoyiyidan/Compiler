//
// Created by 赵鲲翔 on 2024/10/28.
//
#include "Analysis.h"

void Analysis::visit(const FunctionDec &node) {
    node.accept(*this);
}
void Analysis::visit(const compoundstmt &node) {

}