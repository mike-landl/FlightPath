#include "Recorder.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

namespace FlightData
{
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

    TEST_CASE("[Recorder] Read File", "[Recorder]")
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
