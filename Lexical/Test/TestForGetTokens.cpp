#include "../APIOfLexical.h"
#include "gtest/gtest.h"
#include "a.h"
//  need to write the test for the function gettoken
TEST(FactorialTest, kkk) {
    EXPECT_EQ(Factorial(0), 1);
}
TEST(gettokenTest, HandlesInput) {
    std::vector<std::pair<std::string,std::string> > tokens = gettoken("source1.cpp");
    EXPECT_EQ(tokens[0].first, "KeyWord");
    EXPECT_EQ(tokens[0].second, "int");
    EXPECT_EQ(tokens[1].first, "KeyWord");
    EXPECT_EQ(tokens[1].second, "main");
    EXPECT_EQ(tokens[2].first, "SEP");
    EXPECT_EQ(tokens[2].second, "(");
    EXPECT_EQ(tokens[3].first, "SEP");
    EXPECT_EQ(tokens[3].second, ")");
    EXPECT_EQ(tokens[4].first, "SEP");
    EXPECT_EQ(tokens[4].second, "{");
    EXPECT_EQ(tokens[5].first, "KeyWord");
    EXPECT_EQ(tokens[5].second, "return");
    EXPECT_EQ(tokens[6].first, "NUM");
    EXPECT_EQ(tokens[6].second, "0");
    EXPECT_EQ(tokens[7].first, "SEP");
    EXPECT_EQ(tokens[7].second, ";");
    EXPECT_EQ(tokens[8].first, "SEP");
    EXPECT_EQ(tokens[8].second, "}");

}