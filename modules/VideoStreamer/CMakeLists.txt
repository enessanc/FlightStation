set(TEST_VideoStreamer OFF)

add_library(VideoStreamer
        STATIC
        #Headers
        include/VideoStreamer/VideoStreamer.h
        #Implementations
        impl/VideoStreamer.cpp
)

target_include_directories(VideoStreamer PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(VideoStreamer
        PUBLIC TSML GStreamerInterface)

if(TEST_VideoStreamer)
    add_subdirectory(test)
endif()