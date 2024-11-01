add_executable(TestForSyntax a.cpp
        TestHelper.cpp
)
target_link_libraries(TestForSyntax gtest gtest_main)
add_test(NAME TestForSyntax COMMAND TestForSemantic)