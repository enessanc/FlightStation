enable_testing()

add_executable(
        VideoStreamerTest
        test_main.cpp
)
target_link_libraries(
        VideoStreamerTest
        PUBLIC
        GTest::gtest_main
        FSClient
)

add_test(VideoStreamerTestCMAKE VideoStreamerTest)