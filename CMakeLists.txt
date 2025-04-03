cmake_minimum_required(VERSION 3.19)

project(
    FlightPath
    VERSION "0.1.0"
    DESCRIPTION "Reconstructs a Fight Path based on IMU data."
    LANGUAGES C CXX
)

# usefull for some tools and neovim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set c++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add catch2 dependency via fetch content
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

# add main project (library and executeable)
add_subdirectory(src)

# add unit tests
add_subdirectory(tests)
