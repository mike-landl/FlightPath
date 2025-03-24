#include <iostream>
#include <print>
#include <filesystem>

#include "Log.hpp"
#include "Error.hpp"
#include "Solver.hpp"

auto main() -> int
{
    std::filesystem::current_path(PROJECT_ROOT_PATH);

    try
    {
        FlightData::Solver solver;
        solver.Run();
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
