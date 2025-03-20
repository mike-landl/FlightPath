#include <iostream>
#include <print>

#define CATCH_CONFIG_RUNNER
#include <catch2/catch_session.hpp> 

#include "Matrix.hpp"
#include "Log.hpp"

auto main([[maybe_unused]] int argc, char* argv[]) -> int
{
    FlightData::Log::Debug("Hello World!");
    FlightData::Log::Info("Hello World!");
    FlightData::Log::Warn("Hello World!");
    FlightData::Log::Error("Hello World!");

    std::println("");
    FlightData::Log::Info("Running unit test:");
    std::vector<const char*> new_argv{ argv[0], "--reporter", "console", "--durations", "yes", "--verbosity", "high", "-#"};
    int result = Catch::Session().run(static_cast<int>(new_argv.size()), const_cast<char**>(new_argv.data()));
    return result;
}