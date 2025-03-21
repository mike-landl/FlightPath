
add_executable(FlightData
    Exception.cpp
    Main.cpp
    Matrix.cpp
    Mat4.cpp
    ReferenceFrame.cpp
    Solver.cpp
    Vec3.cpp
    VelocityState.cpp
)

target_include_directories(FlightData PUBLIC ${PROJECT_SOURCE_DIR})
target_compile_features(FlightData PUBLIC cxx_std_23)
target_link_libraries(FlightData PUBLIC Catch2::Catch2)
if (MSVC)
    target_compile_options(FlightData PUBLIC /W4 /WX)
    target_compile_definitions(FlightData PUBLIC -DNOMINMAX)
endif()
