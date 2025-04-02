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

find_package(Catch2 QUIET)
if (NOT Catch2_FOUND)
    include(FetchContent)
    set(FETCHCONTENT_QUIET OFF)
    FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG v3.8.0
    )
    FetchContent_MakeAvailable(Catch2)
endif()

add_subdirectory(src)
add_subdirectory(tests)