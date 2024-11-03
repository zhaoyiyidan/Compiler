//
// Created by 赵鲲翔 on 2024/10/23.
//

#include "gtest/gtest.h"
#include "../Source//HelperFunction.cpp"

// 测试 evaluateExpression 函数的功能

// 测试算术运算
TEST(evaluateExpression, ArithmeticOperations) {
    EXPECT_EQ(evaluateExpression("(3+5)*4+2").first, 34);
    EXPECT_EQ(evaluateExpression("3+5*4").first, 23);
    EXPECT_EQ(evaluateExpression("10-2*3").first, 4);
    EXPECT_EQ(evaluateExpression("6/3").first, 2);
    EXPECT_EQ(evaluateExpression("7%3").first, 1);
    EXPECT_EQ(evaluateExpression("(2+3)*4").first, 20);
    EXPECT_EQ(evaluateExpression("2+3*4.0").first, 14.0);
    EXPECT_EQ(evaluateExpression("2.0+3*4").first, 14.0);
    EXPECT_EQ(evaluateExpression("2.0+((3.0*4.0)+3%2)*4").first,54.0 );
    EXPECT_EQ(evaluateExpression("!true+0+2").first,2);
    EXPECT_EQ(evaluateExpression("3%2").first,1);
}

// 测试算术结果类型
TEST(evaluateExpression, ArithmeticTypeCheck) {
    EXPECT_EQ(evaluateExpression("3+5").second, "int");
    EXPECT_EQ(evaluateExpression("3+5.0").second, "double");
    EXPECT_EQ(evaluateExpression("6.0/3").second, "double");
}

// 测试逻辑运算
TEST(evaluateExpression, LogicalOperations) {
    EXPECT_EQ(evaluateExpression("true && false").first, 0);
    EXPECT_EQ(evaluateExpression("true || false").first, 1);
    EXPECT_EQ(evaluateExpression("!true").first, 0);
    EXPECT_EQ(evaluateExpression("!false").first, 1);
}

// 测试逻辑运算结果类型
TEST(evaluateExpression, LogicalTypeCheck) {
    EXPECT_EQ(evaluateExpression("true && false").second, "bool");
    EXPECT_EQ(evaluateExpression("true || false").second, "bool");
    EXPECT_EQ(evaluateExpression("!true").second, "bool");
    EXPECT_EQ(evaluateExpression("1 == 1").second, "bool");
}

// 测试关系运算
TEST(evaluateExpression, RelationalOperations) {
    EXPECT_EQ(evaluateExpression("5 > 3").first, 1);
    EXPECT_EQ(evaluateExpression("5 < 3").first, 0);
    EXPECT_EQ(evaluateExpression("5 >= 5").first, 1);
    EXPECT_EQ(evaluateExpression("5 <= 4").first, 0);
    EXPECT_EQ(evaluateExpression("5 == 5").first, 1);
    EXPECT_EQ(evaluateExpression("5 != 5").first, 0);
}

// 测试关系运算结果类型
TEST(evaluateExpression, RelationalTypeCheck) {
    EXPECT_EQ(evaluateExpression("5 > 3").second, "bool");
    EXPECT_EQ(evaluateExpression("5 == 5").second, "bool");
    EXPECT_EQ(evaluateExpression("5 != 5").second, "bool");
}

// 测试字符处理
TEST(evaluateExpression, CharacterOperations) {
    EXPECT_EQ(evaluateExpression("'A' + 1").first, 'A' + 1);
    EXPECT_EQ(evaluateExpression("'A' == 65").first, 1);
    EXPECT_EQ(evaluateExpression("'B' != 'A'").first, 1);
}

// 测试字符结果类型
TEST(evaluateExpression, CharacterTypeCheck) {
    EXPECT_EQ(evaluateExpression("'A' + 1").second, "int");
    EXPECT_EQ(evaluateExpression("'A'").second, "char");
}

// 测试混合类型运算
TEST(evaluateExpression, MixedTypeOperations) {
    EXPECT_EQ(evaluateExpression("3.5 + 1.5").first, 5.0);
    EXPECT_EQ(evaluateExpression("2 + 3.5").first, 5.5);
    EXPECT_EQ(evaluateExpression("(3 > 2) && (2 < 3)").first, 1);
}

// 测试混合类型结果类型
TEST(evaluateExpression, MixedTypeCheck) {
    EXPECT_EQ(evaluateExpression("3.5 + 1.5").second, "double");
    EXPECT_EQ(evaluateExpression("2 + 3.5").second, "double");
    EXPECT_EQ(evaluateExpression("(3 > 2) && (2 < 3)").second, "bool");
}





