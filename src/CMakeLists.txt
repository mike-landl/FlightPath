
add_library(FlightDataLib
    Exception.cpp
    Recorder.cpp
    ReferenceFrame.cpp
    Solver.cpp
)

target_include_directories(FlightDataLib
    PUBLIC ${PROJECT_SOURCE_DIR}
)

target_compile_features(FlightDataLib
    PUBLIC cxx_std_23
)

if (MSVC)
    target_compile_options(FlightDataLib
        PUBLIC /W4 /WX
    )

    target_compile_definitions(FlightDataLib 
        PUBLIC -DNOMINMAX 
        PUBLIC PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
    )
endif()

add_executable(FlightData
    main.cpp
)

target_link_libraries(FlightData
    PRIVATE FlightDataLib
)
