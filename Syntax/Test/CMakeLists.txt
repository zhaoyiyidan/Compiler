add_executable(TestForSemantic a.cpp
        TestHelper.cpp
        TestHelper.h)
target_link_libraries(TestForSemantic gtest gtest_main)
add_test(NAME TestForSemantic COMMAND TestForSemantic)