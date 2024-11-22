//
// Created by 赵鲲翔 on 2024/11/21.
//

#include "HelperFunction.h"
std::pair<std::string, std::string> split(std::string str, std::string delimiter) {
    size_t pos = 0;
    std::string token;
    pos = str.find(delimiter);
    token = str.substr(0, pos);
    str.erase(0, pos + delimiter.length());
    return std::make_pair(token, str);
}