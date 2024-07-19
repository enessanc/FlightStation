set(TEST_VideoStreamer OFF)

find_package(OpenCV REQUIRED)

add_library(VideoStreamer
        STATIC
        #Headers
        include/VideoStreamer/VideoStreamer.h
        #Implementations
        impl/VideoStreamer.cpp
)

target_include_directories(VideoStreamer PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${OpenCV_INCLUDE_DIRS})

target_link_libraries(VideoStreamer PUBLIC TSML GStreamerInterface FGSCommon ${OpenCV_LIBS})

if(TEST_VideoStreamer)
    add_subdirectory(test)
endif()