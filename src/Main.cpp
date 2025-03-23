#include <iostream>
#include <print>

#define CATCH_CONFIG_RUNNER
#include <catch2/catch_session.hpp> 

#include "Log.hpp"
#include "Error.hpp"
#include "Solver.hpp"

static auto RunUnitTests([[maybe_unused]]int argc, char* argv[]) -> void
{
    FlightData::Log::Info("Running unit test:");
    std::vector<const char*> new_argv{ argv[0], "--reporter", "console", "--durations", "yes", "--verbosity", "high", "-#"};
    const int result = Catch::Session().run(static_cast<int>(new_argv.size()), const_cast<char**>(new_argv.data()));
    FlightData::Ensure(result == EXIT_SUCCESS, "Unit Tests failed.");
}

static auto RunFlightData() -> void
{
    FlightData::Solver solver;
    solver.Run();
}

auto main(int argc, char* argv[]) -> int
{
    try
    {
        RunUnitTests(argc, argv);
        RunFlightData();
    }
    catch (const FlightData::Exception &err)
    {
        std::println(std::cerr, "{}", err);
    }
    catch (...)
    {
        std::println(std::cerr, "unkown exception");
    }
    return EXIT_SUCCESS;
}