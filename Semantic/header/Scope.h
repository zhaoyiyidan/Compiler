//
// Created by 赵鲲翔 on 2024/10/28.
//

#ifndef COMPILER_SCOPE_H
#define COMPILER_SCOPE_H

#include "Symbol.h"
#include <unordered_map>
class Scope {
    std::unordered_map<std::string,Symbol> symbols;
public:
    void InsertSymbol(const std::string &name,const std::string &type,int memoryLocation){
        auto symbol=Symbol(name,type,memoryLocation);
        symbols.insert(std::make_pair(name,symbol));
    }
    void InsertSymbol(const std::string &name,const std::string &type,double value,int memoryLocation){
        auto symbol=Symbol(name,type,value,memoryLocation);
        symbols.insert(std::make_pair(name,symbol));
    }
    bool ExistSymbol(const std::string &name){
        if(symbols.find(name)!=symbols.end()){
            return true;
        }
        return false;
    }
    std::pair<std::string ,double> GetSymbol(const std::string &name){
        if (ExistSymbol(name)){
            return std::make_pair(symbols.at(name).getType(),symbols.at(name).getValue());
        }
        throw std::runtime_error("No such symbol");
    }
    Scope(){}
};


#endif //COMPILER_SCOPE_H
