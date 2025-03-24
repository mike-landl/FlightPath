#include <iostream>
#include <print>

#include "Log.hpp"
#include "Error.hpp"
#include "Solver.hpp"

auto main() -> int
{
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
