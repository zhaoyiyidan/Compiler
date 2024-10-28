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
    bool ExistSymbol(const std::string &name){
        if(symbols.find(name)!=symbols.end()){
            return true;
        }
        return false;
    }
    Scope(){}
};


#endif //COMPILER_SCOPE_H
