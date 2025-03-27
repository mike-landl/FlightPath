#include "Log.hpp"

#include <sstream>
#include <streambuf>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("[Log] Debug works", "[Log]") {
    std::ostringstream captured_output;
    std::streambuf* old_buf = std::cout.rdbuf(); // save old buffer
    std::cout.rdbuf(captured_output.rdbuf()); // set buffer to captured_output

    FlightData::Log::Debug("Debug");

    std::cout.rdbuf(old_buf); // restore old buffer
    REQUIRE(captured_output.str() == "\x1B[94m[D]\x1B[0m test_Log.cpp:14 Debug\n");
}

TEST_CASE("[Log] Info works", "[Log]") {
    std::ostringstream captured_output;
    std::streambuf* old_buf = std::cout.rdbuf(); // save old buffer
    std::cout.rdbuf(captured_output.rdbuf()); // set buffer to captured_output

    FlightData::Log::Info("Info");

    std::cout.rdbuf(old_buf); // restore old buffer
    REQUIRE(captured_output.str() == "\x1B[92m[I]\x1B[0m Info\n");
}

TEST_CASE("[Log] Warn works", "[Log]") {
    std::ostringstream captured_output;
    std::streambuf* old_buf = std::cout.rdbuf(); // save old buffer
    std::cout.rdbuf(captured_output.rdbuf()); // set buffer to captured_output

    FlightData::Log::Warn("Warn");

    std::cout.rdbuf(old_buf); // restore old buffer
    REQUIRE(captured_output.str() == "\x1B[93m[W]\x1B[0m test_Log.cpp:36 Warn\n");
}

TEST_CASE("[Log] Error works", "[Log]") {
    std::ostringstream captured_output;
    std::streambuf* old_buf = std::cout.rdbuf(); // save old buffer
    std::cout.rdbuf(captured_output.rdbuf()); // set buffer to captured_output

    FlightData::Log::Error("Error");

    std::cout.rdbuf(old_buf); // restore old buffer
    REQUIRE(captured_output.str() == "\x1B[91m[E]\x1B[0m test_Log.cpp:47 Error\n");
}