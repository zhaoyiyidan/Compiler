add_executable(TestForLexical a.cpp
        TestForGetTokens.cpp)
target_link_libraries(TestForLexical gtest gtest_main)
add_test(NAME TestForLexical COMMAND TestForLexical)