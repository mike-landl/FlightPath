cmake_minimum_required(VERSION 3.19)

project(
    FlightPath
    VERSION "0.1.2"
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

# add doxygen-awesome theme
include(FetchContent)
FetchContent_Declare(
    doxygen-awesome-css
    URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/tags/v2.3.4.zip
)
FetchContent_MakeAvailable(doxygen-awesome-css)

# Save the location the files were cloned into
# This allows us to get the path to doxygen-awesome.css
FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)

# Generate the Doxyfile based on Doxyfile.in
set(DOXYFILE_IN ${PROJECT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${PROJECT_SOURCE_DIR}/Doxyfile)
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

# add main project (library and executeable)
add_subdirectory(src)

# add unit tests
add_subdirectory(tests)
