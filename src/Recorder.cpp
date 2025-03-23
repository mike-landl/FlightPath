#include "Recorder.hpp"

#include <fstream>
#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "Error.hpp"
#include "Units.hpp"

namespace FlightData
{
    // overload stream operator for input file stream
    // reads a line and converts units to SI unit
    static std::istream& operator>>(std::istream &input_stream, Entry &entry)
    {
		if (input_stream 
            >> entry.time
            >> entry.longitude
            >> entry.latitude   
            >> entry.altitude 
            >> entry.true_heading
            >> entry.pitch
            >> entry.roll
            >> entry.v_x         
            >> entry.v_y         
            >> entry.v_z      
            >> entry.omega_x   
            >> entry.omega_y   
            >> entry.omega_z
            >> entry.a_x       
            >> entry.a_y       
            >> entry.a_z)
        {
            entry.longitude    = deg2rad(entry.longitude);
            entry.latitude     = deg2rad(entry.latitude);

            entry.true_heading = deg2rad(entry.true_heading);
            entry.pitch        = deg2rad(entry.pitch);
            entry.roll         = deg2rad(entry.roll);

            entry.omega_x      = deg2rad(entry.omega_x);
            entry.omega_y      = deg2rad(entry.omega_y);
            entry.omega_z      = deg2rad(entry.omega_z);
        }
        return input_stream;
    }

    auto Recorder::ReadFile(const std::string &path) -> void
    {
		std::ifstream file(path);
		
		Ensure(file.is_open(), "Recorder: Could not open file {}", path);

        Entry entry{};
		while (file >> entry)
		{
			data_.push_back(entry);
		}
    }

    static auto CheckDouble(const double value, const double expected) -> void
    {
        REQUIRE_THAT(
            value,
            Catch::Matchers::WithinRel(
                expected,
                std::numeric_limits<double>::epsilon()
            )
        );
    }

    TEST_CASE("[recorder] Read File", "[recorder]")
    {
        Recorder recorder;

        recorder.ReadFile("../../../data/UnitTest.txt");
        auto &data = recorder.GetData();
        REQUIRE(data.size() == 2);

        {
            const Entry &entry = data[0];
            CheckDouble(        entry.time,          2733.92);
            CheckDouble(rad2deg(entry.longitude),      15.755530969);
            CheckDouble(rad2deg(entry.latitude),       42.900372544);
            CheckDouble(        entry.altitude,      3657.4);
            CheckDouble(rad2deg(entry.true_heading),  178.9);
            CheckDouble(rad2deg(entry.pitch),           0.2);
            CheckDouble(rad2deg(entry.roll),           -0.4);
            CheckDouble(        entry.v_x,            169.2);
            CheckDouble(        entry.v_y,             -1.0);
            CheckDouble(        entry.v_z,              0.7);
            CheckDouble(rad2deg(entry.omega_x),        -0.030);
            CheckDouble(rad2deg(entry.omega_y),         0.009);
            CheckDouble(rad2deg(entry.omega_z),         0.038);
            CheckDouble(        entry.a_x,              0.00781);
            CheckDouble(        entry.a_y,             -0.00391);
            CheckDouble(        entry.a_z,              0.07031);
        }

        {
            const Entry &entry = data[1];
            CheckDouble(        entry.time,          2733.93);
            CheckDouble(rad2deg(entry.longitude),      15.755531608);
            CheckDouble(rad2deg(entry.latitude),       42.900354289);
            CheckDouble(        entry.altitude,      3657.4);
            CheckDouble(rad2deg(entry.true_heading),  178.9);
            CheckDouble(rad2deg(entry.pitch),           0.2);
            CheckDouble(rad2deg(entry.roll),           -0.4);
            CheckDouble(        entry.v_x,            169.2);
            CheckDouble(        entry.v_y,             -1.0);
            CheckDouble(        entry.v_z,              0.7);
            CheckDouble(rad2deg(entry.omega_x),        -0.032);
            CheckDouble(rad2deg(entry.omega_y),         0.010);
            CheckDouble(rad2deg(entry.omega_z),         0.039);
            CheckDouble(        entry.a_x,              0.00781);
            CheckDouble(        entry.a_y,             -0.00391);
            CheckDouble(        entry.a_z,              0.06641);
        }
    }
}