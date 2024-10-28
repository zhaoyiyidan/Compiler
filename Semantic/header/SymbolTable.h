//
// Created by 赵鲲翔 on 2024/10/21.
//

#ifndef COMPILER_SYMBOLTABLE_H
#define COMPILER_SYMBOLTABLE_H
#include <string>
#include "Scope.h"
#include  <vector>

class SymbolTable {
    std::vector<Scope> scopeStack;
public:
    void EnterScope(){
        scopeStack.emplace_back();
    }
    void ExitScope(){
        if (!scopeStack.empty()){
            scopeStack.pop_back();
        }
        else{
            throw std::runtime_error("No scope to exit");
        }
    }
    void InsertSymbol(const std::string &name,const std::string &type,int memoryLocation){
        if (!scopeStack.empty()){
            scopeStack.back().InsertSymbol(name,type,memoryLocation);
        }
        else{
            throw std::runtime_error("No scope to insert symbol");
        }
    }
    bool ExistSymbol(const std::string &name){
        for (auto it=scopeStack.rbegin();it!=scopeStack.rend();it++){
            if (it->ExistSymbol(name)){
                return true;
            }
        }
        return false;
    }
};


#endif //COMPILER_SYMBOLTABLE_H
