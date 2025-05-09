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

enable_testing()

add_executable(RunTests
    test_Main.cpp
    test_Attitude.cpp
    test_Error.cpp
    test_Exception.cpp
    test_Log.cpp
    test_Mat4.cpp
    test_Vec3.cpp
    test_Position.cpp
    test_Recorder.cpp
    test_ReferenceFrame.cpp
    test_Units.cpp
)

# Link with main project and catch2
target_link_libraries(RunTests
    PRIVATE FlightPathLib
    PRIVATE Catch2::Catch2WithMain
)

target_include_directories(RunTests 
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    )

target_compile_definitions(RunTests
    PRIVATE PROJECT_ROOT_PATH="${PROJECT_SOURCE_DIR}"
)

# Add compiler warnings for clang and msvc and interpret warnings as errors
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(RunTests 
        PRIVATE -Wall -Wextra -Wpedantic -Werror
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(RunTests 
        PRIVATE /W4 /WX
    )
endif()

# Make ctest discover the tests
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(RunTests)
add_test(NAME RunTests COMMAND RunTests)
