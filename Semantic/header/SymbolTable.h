//
// Created by 赵鲲翔 on 2024/10/21.
//

#ifndef COMPILER_SYMBOLTABLE_H
#define COMPILER_SYMBOLTABLE_H
#include <map>
#include <string>
class SymbolTable {
public:
    std::map<std::string, std::string> table;
    void insert(std::string Var, std::string Value){
        table[Var]=Value;
    }
    bool Exist(std::string Var){
        return table.find(Var)!=table.end();
    }
    std::string Find(std::string Var){
        return table[Var];
    }

};


#endif //COMPILER_SYMBOLTABLE_H
