set(TEST_FSClient OFF)

add_library(FSClient
        STATIC
        #Header Files
        include/FSClient/FGSCommon.h
        include/FSClient/FSClient.h
        #Implementations
        impl/FSClient.cpp
)

target_include_directories(FSClient PUBLIC
                          ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(FSClient PUBLIC TSML NL)

if(TEST_FSClient)
    add_subdirectory(test)
endif()