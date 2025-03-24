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

# Add the src folder so your tests can find production headers like Mat4.hpp and Vec3.hpp
target_include_directories(RunTests PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
)

target_compile_features(RunTests PUBLIC cxx_std_23)
if (MSVC)
    target_compile_options(RunTests PUBLIC /W4 /WX)
endif()

# register tests with ctest
add_test(NAME RunTests COMMAND RunTests)