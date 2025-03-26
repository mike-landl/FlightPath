cmake_minimum_required(VERSION 3.19)

project(
    FlightData 
    VERSION "0.1.0"
    DESCRIPTION "Fight Data"
    LANGUAGES C CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor/Catch2-3.8.0)

add_subdirectory(src)
add_subdirectory(tests)