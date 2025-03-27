
add_library(FlightDataLib
    Exception.cpp
    Recorder.cpp
    ReferenceFrame.cpp
    Solver.cpp
)

target_include_directories(FlightDataLib
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(FlightDataLib 
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

add_executable(FlightData
    Main.cpp
)

target_include_directories(FlightData
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(FlightData
    PRIVATE PROJECT_ROOT_PATH="${PROJECT_SOURCE_DIR}"
)

target_link_libraries(FlightData
    PRIVATE FlightDataLib
)
