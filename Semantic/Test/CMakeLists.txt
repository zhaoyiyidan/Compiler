add_executable(TestForSemantic a.cpp)
target_link_libraries(TestForSemantic gtest gtest_main)
add_test(NAME TestForSemantic COMMAND TestForSyntax)