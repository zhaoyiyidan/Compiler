//
// Created by 赵鲲翔 on 2024/10/11.
//

#include "../header/module.h"
// how do think the return type
#include "../header/Declaration.h"
#include "../header/statement.h"
#include "../header/Type.h"

// how do think the return type
std::vector<std::string> module::search(std::string order) {
    // use three pointers to iterate the tree
    // use a vector string to store the result
    auto iteraterOfdel = del.begin();
    auto iteraterOfstmt = stmt.begin();
    auto iteraterOftype = type.begin();
    std::vector<std::string> result;
    for (int i =0;i<iterateOrder.size();i++){
        if (iterateOrder[i]==1){
            // iterate the del
           auto temp = (*iteraterOfdel)->searchDel(order);
           for (auto i:temp){
               result.push_back(i);
           }

        }
        else if (iterateOrder[i]==2){
            // iterate the stmt
            auto temp = (*iteraterOfstmt)->searchStmt(order);
            for (auto i:temp){
                result.push_back(i);
            }

        }
        else if (iterateOrder[i]==3){
            // iterate the type
            auto temp = (*iteraterOftype)->searchType(order);
            for (auto i:temp){
                result.push_back(i);
            }
        }

    }
    return result;
    // Implement the rest of the search logic
}