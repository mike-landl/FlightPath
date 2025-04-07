#include <iostream>
#include <filesystem>

#include "Log.hpp"
#include "Error.hpp"
#include "Application.hpp"

/** 
 * \mainpage About
 *
 * \section intro_sec Introduction
 * This project processes a datalogger file from a flight simulator and reconstructs the flight path using only data from the onboard **inertial measurement unit (IMU)**.
 * (i.e. body-fixed linear acceleration and angular velocity)
 *
 * \section usage_sec Usage
 * For guidance on how to build and use this project, please refer to the `README.md` or visit the [GitHub repository](https://github.com/mike-landl/FlightPath).
 */

auto main() -> int
{
    std::filesystem::current_path(PROJECT_ROOT_PATH);

    try
    {
        FlightPath::Application app;
        app.Run();
    }
    catch (const FlightPath::Exception &err)
    {
        std::cerr << std::format("{}", err) << std::endl;
    }
    catch (...)
    {
        std::cerr << "unkown exception" << std::endl;
    }
    return EXIT_SUCCESS;
}
