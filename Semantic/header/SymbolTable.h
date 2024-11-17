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
    bool structFlag=false;
    std::string structName="null";
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
        if (!structFlag){
        if (!scopeStack.empty()){
            scopeStack.back().InsertSymbol(name,type,memoryLocation);
        }
        else{
            throw std::runtime_error("No scope to insert symbol");
        }
        }
        else {
            auto thesymbol=GetTheSymbol(structName);
            auto symbolinvector=Symbol(name,type,memoryLocation);
            thesymbol.ManySymbol.push_back(symbolinvector);
        }

    }
    void InsertSymbol(const std::string &name,const std::string &type,double value,int memoryLocation){
        if (!structFlag){
        if (!scopeStack.empty()){
            scopeStack.back().InsertSymbol(name,type,value,memoryLocation);
        }
        else{
            throw std::runtime_error("No scope to insert symbol");
        }
        }
        else{
            auto thesymbol=GetTheSymbol(structName);
            auto symbolinvector=Symbol(name,type,value,memoryLocation);
            thesymbol.ManySymbol.push_back(symbolinvector);
        }
    }
    void InsertSymbol(const Symbol theSymbol){
        if (!scopeStack.empty()){
            scopeStack.back().InsertSymbol(theSymbol);
        }
        else{
            throw std::runtime_error("No scope to insert symbol");
        }
    }
    void InsertSymbol(const std::string &name){
        if (!scopeStack.empty()){
            scopeStack.back().InsertSymbol(name);
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
    Symbol GetTheSymbol(std::string name){
        for (auto it=scopeStack.rbegin();it!=scopeStack.rend();it++){
            if (it->ExistSymbol(name)){
                return it->GetTheSymbol(name);
            }
        }
        throw std::runtime_error("No such symbol");
    }
    // first is type, second is value
    std::pair<std::string ,double> GetSymbol(const std::string &name){
        for (auto it=scopeStack.rbegin();it!=scopeStack.rend();it++){
            if (it->ExistSymbol(name)){
                return it->GetSymbol(name);
            }
        }
        throw std::runtime_error("No such symbol");
    }
};


#endif //COMPILER_SYMBOLTABLE_H
