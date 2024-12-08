//
// Created by 赵鲲翔 on 2024/11/21.
//

#ifndef COMPILER_HELPERFUNCTION_H
#define COMPILER_HELPERFUNCTION_H

#include <string>
std::pair<std::string, std::string> split(std::string str, std::string delimiter) ;
void HandleException(std::string cpppath,std::string llpath);
#endif //COMPILER_HELPERFUNCTION_H
