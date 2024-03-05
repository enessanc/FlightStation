add_executable(FlightStation main.cpp)

target_link_libraries(FlightStation PRIVATE
                      FSClient PX4Controller VideoStreamer)