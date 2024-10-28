//
// Created by 赵鲲翔 on 2024/10/28.
//

#ifndef COMPILER_SYMBOL_H
#define COMPILER_SYMBOL_H

#include <string>
class Symbol {
    std::string name;// temporary not use
    std::string type;// the type of this IDEN
    int memoryLocation;
public:
    Symbol(const std::string& name, const std::string& type, int memoryLocation) : name(name), type(type), memoryLocation(memoryLocation) {}
    const std::string& getName() const {
        return name;
    }
    const std::string& getType() const {
        return type;
    }
    int getMemoryLocation() const {
        return memoryLocation;
    }
};


#endif //COMPILER_SYMBOL_H
