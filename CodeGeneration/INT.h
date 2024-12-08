//
// Created by 赵鲲翔 on 2024/12/1.
//

#ifndef COMPILER_INT_H
#define COMPILER_INT_H

#include <string>
#include <iostream>
#include <cstdlib>
class INT {
public:
    int number;
    INT(int a){number=a;}
    void exe(std::string a ,std::string b){
     std::string sss="clang++  " + a+" -o "+b;
     system(sss.c_str());
    }
};


#endif //COMPILER_INT_H
