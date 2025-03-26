enable_testing()

add_executable(RunTests
    test_main.cpp
    test_Mat4.cpp
    test_Vec3.cpp
    test_Recorder.cpp
    test_ReferenceFrame.cpp
    test_Units.cpp
)

target_link_libraries(RunTests
    PRIVATE FlightDataLib
    PRIVATE Catch2::Catch2
)

target_include_directories(RunTests 
    PRIVATE ${PROJECT_SOURCE_DIR}/src
    )

target_compile_definitions(RunTests
    PRIVATE PROJECT_ROOT_PATH="${PROJECT_SOURCE_DIR}"
)

# Add compiler warnings for clang and msvc and interpret warnings as errors
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(FlightDataLib 
        PRIVATE -Wall -Wextra -Wpedantic -Werror
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(FlightDataLib 
        PRIVATE /W4 /WX
    )
endif()

# register tests with ctest -- todo: fix-me
add_test(NAME RunTests COMMAND RunTests)