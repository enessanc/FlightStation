add_executable(FlightStation main.cpp)

target_link_libraries(FlightStation PUBLIC
                      FSClient PX4Controller VideoStreamer)