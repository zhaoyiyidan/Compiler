//
// Created by 赵鲲翔 on 2024/10/10.
//
#include "gtest/gtest.h"
int Factorial(int n){
    return n <= 1 ? 1 : n * Factorial(n - 1);
}
// Tests factorial of 0.
TEST(FactorialTest, sHandlesZeroInput) {
EXPECT_EQ(Factorial(0), 1);
}

// Tests factorial of positive numbers.
TEST(FactorialTest, bHandlesPositiveInput) {
EXPECT_EQ(Factorial(1), 1);
EXPECT_EQ(Factorial(2), 2);
EXPECT_EQ(Factorial(3), 6);
EXPECT_EQ(Factorial(8), 40320);
}

class FooTest:public testing::Test{
protected:
};
TEST_F(FooTest,Test1){
EXPECT_EQ(1,1);
}
