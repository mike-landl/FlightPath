#include <iostream>
#include <filesystem>

#include "Log.hpp"
#include "Error.hpp"
#include "Application.hpp"

auto main() -> int
{
    std::filesystem::current_path(PROJECT_ROOT_PATH);

    try
    {
        FlightData::Application app;
        app.Run();
    }
    catch (const FlightData::Exception &err)
    {
        std::cerr << std::format("{}", err) << std::endl;
    }
    catch (...)
    {
        std::cerr << "unkown exception" << std::endl;
    }
    return EXIT_SUCCESS;
}
