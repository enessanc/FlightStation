add_executable(
        PX4ControllerTest
        test_main.cpp
)

target_link_libraries(
        PX4ControllerTest
        PUBLIC
        PX4Controller
)

