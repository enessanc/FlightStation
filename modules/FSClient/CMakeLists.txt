set(TEST_FSClient OFF)

find_package(Threads REQUIRED)

add_library(FSClient
        STATIC
        #Header Files
        include/FSClient/FSClient.h
        #Implementations
        impl/FSClient.cpp
)

target_include_directories(FSClient PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)


target_link_libraries(FSClient PUBLIC TSML NL FGSCommon ${CMAKE_THREAD_LIBS_INIT})

if(TEST_FSClient)
    add_subdirectory(test)
endif()