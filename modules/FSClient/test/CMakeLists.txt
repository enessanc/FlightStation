enable_testing()

add_executable(
        FSClientTest
        test_main.cpp
)
target_link_libraries(
        FSClientTest
        PUBLIC
        GTest::gtest_main
        FSClient
)

add_test(FSClientTestCMAKE FSClientTest)