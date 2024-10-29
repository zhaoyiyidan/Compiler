#include "../APIOfLexical.h"
#include"../APIOfLexical.cpp"
#include "gtest/gtest.h"
#include "a.h"
#include "../tem.h"
//  need to write the test for the function gettoken
TEST(FactorialTest, kkk) {
    EXPECT_EQ(Factorial(0), 1);
}

TEST(Factorials,qqqq){
    EXPECT_EQ(Factorials(3),6);
}

TEST(gettokenTest, source1) {
    std::vector<std::pair<std::string,std::string> > tokens = gettoken("/Users/zhaokunxiang/clion/compiler/Lexical/Test/source1.cpp");
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

TEST(gettokenTest, source2) {
    std::vector<std::pair<std::string, std::string>> tokens = gettoken("/Users/zhaokunxiang/clion/compiler/Lexical/Test/source2.cpp");
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
    EXPECT_EQ(tokens[5].second, "int");
    EXPECT_EQ(tokens[6].first, "IDEN");
    EXPECT_EQ(tokens[6].second, "a");
    EXPECT_EQ(tokens[7].first, "OP");
    EXPECT_EQ(tokens[7].second, "=");
    EXPECT_EQ(tokens[8].first, "NUM");
    EXPECT_EQ(tokens[8].second, "1");
    EXPECT_EQ(tokens[9].first, "SEP");
    EXPECT_EQ(tokens[9].second, ";");
    EXPECT_EQ(tokens[10].first, "IDEN");
    EXPECT_EQ(tokens[10].second, "a");
    EXPECT_EQ(tokens[11].first, "OP");
    EXPECT_EQ(tokens[11].second, "=");
    EXPECT_EQ(tokens[12].first, "NUM");
    EXPECT_EQ(tokens[12].second, "2");
    EXPECT_EQ(tokens[13].first, "SEP");
    EXPECT_EQ(tokens[13].second, ";");
    EXPECT_EQ(tokens[14].first, "KeyWord");
    EXPECT_EQ(tokens[14].second, "int");
    EXPECT_EQ(tokens[15].first, "IDEN");
    EXPECT_EQ(tokens[15].second, "b");
    EXPECT_EQ(tokens[16].first, "SEP");
    EXPECT_EQ(tokens[16].second, ";");
    EXPECT_EQ(tokens[17].first, "IDEN");
    EXPECT_EQ(tokens[17].second, "b");
    EXPECT_EQ(tokens[18].first, "OP");
    EXPECT_EQ(tokens[18].second, "=");
    EXPECT_EQ(tokens[19].first, "NUM");
    EXPECT_EQ(tokens[19].second, "3");
    EXPECT_EQ(tokens[20].first, "SEP");
    EXPECT_EQ(tokens[20].second, ";");
    EXPECT_EQ(tokens[21].first, "KeyWord");
    EXPECT_EQ(tokens[21].second, "if");
    EXPECT_EQ(tokens[22].first, "SEP");
    EXPECT_EQ(tokens[22].second, "(");
    EXPECT_EQ(tokens[23].first, "IDEN");
    EXPECT_EQ(tokens[23].second, "a");
    EXPECT_EQ(tokens[24].first, "OP");
    EXPECT_EQ(tokens[24].second, "==");
    EXPECT_EQ(tokens[25].first, "NUM");
    EXPECT_EQ(tokens[25].second, "2");
    EXPECT_EQ(tokens[26].first, "SEP");
    EXPECT_EQ(tokens[26].second, ")");
    EXPECT_EQ(tokens[27].first, "SEP");
    EXPECT_EQ(tokens[27].second, "{");
    EXPECT_EQ(tokens[28].first, "IDEN");
    EXPECT_EQ(tokens[28].second, "a");
    EXPECT_EQ(tokens[29].first, "OP");
    EXPECT_EQ(tokens[29].second, "=");
    EXPECT_EQ(tokens[30].first, "NUM");
    EXPECT_EQ(tokens[30].second, "3");
    EXPECT_EQ(tokens[31].first, "SEP");
    EXPECT_EQ(tokens[31].second, ";");
    EXPECT_EQ(tokens[32].first, "SEP");
    EXPECT_EQ(tokens[32].second, "}");
    EXPECT_EQ(tokens[33].first, "KeyWord");
    EXPECT_EQ(tokens[33].second, "else");
    EXPECT_EQ(tokens[34].first, "SEP");
    EXPECT_EQ(tokens[34].second, "{");
    EXPECT_EQ(tokens[35].first, "IDEN");
    EXPECT_EQ(tokens[35].second, "a");
    EXPECT_EQ(tokens[36].first, "OP");
    EXPECT_EQ(tokens[36].second, "=");
    EXPECT_EQ(tokens[37].first, "NUM");
    EXPECT_EQ(tokens[37].second, "4");
    EXPECT_EQ(tokens[38].first, "SEP");
    EXPECT_EQ(tokens[38].second, ";");
    EXPECT_EQ(tokens[39].first, "SEP");
    EXPECT_EQ(tokens[39].second, "}");
    EXPECT_EQ(tokens[40].first, "SEP");
    EXPECT_EQ(tokens[40].second, "}");
}

TEST(gettokenTest,source3){
    auto tokens = gettoken("/Users/zhaokunxiang/clion/compiler/Lexical/Test/source3.cpp");
    EXPECT_EQ(tokens[0].first,"KeyWord");
    EXPECT_EQ(tokens[0].second,"double");
    EXPECT_EQ(tokens[1].first,"IDEN");
    EXPECT_EQ(tokens[1].second,"Return");
    EXPECT_EQ(tokens[2].first,"NUM");
    EXPECT_EQ(tokens[2].second,"1234");

}