#include "Log.hpp"

#include "TestHelper.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("[Log] Debug works", "[Log]")
{
    // lambda without captures or parameters for passing anonymous inline function
    auto console_output = CaptureOutput([](){FlightPath::Log::Debug("Debug");});
    REQUIRE(console_output == "\x1B[94m[D]\x1B[0m test_Log.cpp:11 Debug\n");
}

TEST_CASE("[Log] Info works", "[Log]")
{
    auto console_output = CaptureOutput([](){FlightPath::Log::Info("Info");});
    REQUIRE(console_output == "\x1B[92m[I]\x1B[0m Info\n");
}

TEST_CASE("[Log] Warn works", "[Log]")
{
    auto console_output = CaptureOutput([](){FlightPath::Log::Warn("Warn");});
    REQUIRE(console_output == "\x1B[93m[W]\x1B[0m test_Log.cpp:23 Warn\n");
}

TEST_CASE("[Log] Error works", "[Log]")
{
    auto console_output = CaptureOutput([](){FlightPath::Log::Error("Error");});
    REQUIRE(console_output == "\x1B[91m[E]\x1B[0m test_Log.cpp:29 Error\n");
}
