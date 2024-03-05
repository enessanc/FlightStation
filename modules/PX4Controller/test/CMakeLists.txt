enable_testing()

add_executable(
        PX4ControllerTest
        test_main.cpp
)
target_link_libraries(
        PX4ControllerTest
        PUBLIC
        GTest::gtest_main
        FSClient
)

add_test(PX4ControllerTestCMAKE PX4ControllerTest)