cmake_minimum_required(VERSION 3.19)

project(
    FlightData 
    VERSION "0.0.1"
    DESCRIPTION "Fight Data"
    LANGUAGES C CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendor/Catch2-3.8.0)

add_subdirectory(src)
