//
// Created by 赵鲲翔 on 2024/10/23.
//

#ifndef COMPILER_TEM_H
#define COMPILER_TEM_H


int Factorials(int n){
    if(n==0){
        return 1;
    }
    else{
        return n*Factorials(n-1);
    }
}


#endif //COMPILER_TEM_H
