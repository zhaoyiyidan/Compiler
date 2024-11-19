//
// Created by 赵鲲翔 on 2024/10/28.
//

#ifndef COMPILER_SYMBOL_H
#define COMPILER_SYMBOL_H

#include <string>
#include <vector>
#include <limits>
class Symbol {
    public:
    std::string name;// temporary not use
    std::string type;// the type of this IDEN
    double value=std::numeric_limits<double>::quiet_NaN();// the value of this IDEN
    int memoryLocation;
    std::vector<Symbol> ManySymbol;// it is used to store the symbol of the struct and array

    Symbol(const std::string& name, const std::string& type, int memoryLocation) : name(name), type(type), memoryLocation(memoryLocation) {}
    Symbol(const std::string& name, const std::string& type, int memoryLocation, std::vector<Symbol> symbols) : name(name), type(type), memoryLocation(memoryLocation), ManySymbol(symbols) {}
    const std::string& getName() const {
        return name;
    }
    Symbol(const std::string& name, const std::string& type, double value, int memoryLocation) : name(name), type(type), value(value), memoryLocation(memoryLocation) {}
    const std::string& getType() const {
        return type;
    }
    int getMemoryLocation() const {
        return memoryLocation;
    }
    double getValue() const {
        return value;
    }
    // set the value
    void SetValue(double value){
        this->value=value;
    }
};


#endif //COMPILER_SYMBOL_H
