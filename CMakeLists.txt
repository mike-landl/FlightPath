cmake_minimum_required(VERSION 3.24)

project(
    FlightPath
    VERSION "0.1.8"
    DESCRIPTION "Reconstructs a Fight Path based on IMU data."
    LANGUAGES C CXX
)

# usefull for some tools and neovim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set c++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# default options for configuring tests and documentation
option(ENABLE_TESTS "Enable unit tests"       ON )
option(ENABLE_DOCS  "Enable building of docs" OFF)

# add main project (library and executeable)
add_subdirectory(src)

# add unit tests
if(ENABLE_TESTS)
    add_subdirectory(tests)
endif()

# add awesome-doxygen template
if(ENABLE_DOCS)
    add_subdirectory()
endif()