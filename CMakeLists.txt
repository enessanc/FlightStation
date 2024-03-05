cmake_minimum_required(VERSION 3.27)
project(FlightStation)

set(CMAKE_CXX_STANDARD 20)
set(TEST_SUBMODULES OFF)
set(TEST_FS OFF)

add_subdirectory(external/GStreamer)
add_subdirectory(external/TSML)
add_subdirectory(external/NL)

add_subdirectory(modules)

if(TEST_FS)

    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    FetchContent_MakeAvailable(googletest)

    if(TEST_SUBMODULES)

    else()

    endif()
else()
    add_subdirectory(source)
endif()






