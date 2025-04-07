# Build code as static library
add_library(FlightPathLib
    Exception.cpp
    Recorder.cpp
    ReferenceFrame.cpp
    Application.cpp
)

target_include_directories(FlightPathLib
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(FlightPathLib 
    PRIVATE PROJECT_ROOT_PATH="${PROJECT_SOURCE_DIR}"
)

# Add compiler warnings for clang and msvc and interpret warnings as errors
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(FlightPathLib 
        PRIVATE -Wall -Wextra -Wpedantic -Werror
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(FlightPathLib 
        PRIVATE /W4 /WX
    )
endif()

# Add an executable based that uses the static library
add_executable(FlightPath
    Main.cpp
)

target_include_directories(FlightPath
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(FlightPath
    PRIVATE PROJECT_ROOT_PATH="${PROJECT_SOURCE_DIR}"
)

target_link_libraries(FlightPath
    PRIVATE FlightPathLib
)
