set(TEST_PX4Controller OFF)

add_library(PX4Controller
        STATIC
        #Headers
        include/PX4Controller/PX4Controller.h
        include/PX4Controller/CoordTranformer.h
        #Implementations
        impl/PX4Controller.cpp
        impl/CoordLocalizer.cpp
)

target_include_directories(PX4Controller PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(PX4Controller PUBLIC TSML FGSCommon)

if(TEST_PX4Controller)
    add_subdirectory(test)
endif()