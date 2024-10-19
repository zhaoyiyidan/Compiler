//
// Created by 赵鲲翔 on 2024/10/11.
//

#ifndef COMPILER_APIOFLEXICAL_H
#define COMPILER_APIOFLEXICAL_H

#include <vector>
#include <utility>
#include <string>
// you can use this function to get the token array, the frist element of the pair is the token type, the second element of the pair is the token value
// such ad <IntegerLiteral,3> <IDEN,a> <keyword,if> ,etc.
std::vector<std::pair<std::string,std::string> > gettoken();
// you can use this function to read the source code file.
void readfile(std::string filename);


#endif //COMPILER_APIOFLEXICAL_H
