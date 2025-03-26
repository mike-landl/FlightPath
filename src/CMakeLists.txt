
add_library(FlightDataLib
    Exception.cpp
    Recorder.cpp
    ReferenceFrame.cpp
    Solver.cpp
)

target_include_directories(FlightDataLib
    PRIVATE ${PROJECT_SOURCE_DIR}
)

target_compile_features(FlightDataLib
    PRIVATE cxx_std_23
)

target_compile_definitions(FlightDataLib 
    PUBLIC PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(FlightDataLib PUBLIC -Wall -Wextra -Wpedantic -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(FlightDataLib PUBLIC /W4 /WX)
endif()

add_executable(FlightData
    Main.cpp
)

target_link_libraries(FlightData
    PRIVATE FlightDataLib
)
