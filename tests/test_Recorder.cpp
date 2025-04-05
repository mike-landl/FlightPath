#include "Recorder.hpp"
#include "TestFloatHelper.hpp"

#include <catch2/catch_test_macros.hpp>


namespace FlightPath
{
    TEST_CASE("[Recorder] Read File", "[Recorder]")
    {
        Recorder recorder;

        recorder.ReadFile(std::string(PROJECT_ROOT_PATH) + "/data/UnitTest.txt");
        auto &data = recorder.GetData();
        REQUIRE(data.size() == 2);

        {
            const Entry &entry = data[0];
            CheckReal<double>(                entry.time,          2733.92);
            CheckReal<double>(rad2deg<double>(entry.longitude),      15.755530969);
            CheckReal<double>(rad2deg<double>(entry.latitude),       42.900372544);
            CheckReal<double>(                entry.altitude,      3657.4);
            CheckReal<double>(rad2deg<double>(entry.true_heading),  178.9);
            CheckReal<double>(rad2deg<double>(entry.pitch),           0.2);
            CheckReal<double>(rad2deg<double>(entry.roll),           -0.4);
            CheckReal<double>(                entry.v_x,            169.2);
            CheckReal<double>(                entry.v_y,             -1.0);
            CheckReal<double>(                entry.v_z,              0.7);
            CheckReal<double>(rad2deg<double>(entry.omega_x),        -0.030);
            CheckReal<double>(rad2deg<double>(entry.omega_y),         0.009);
            CheckReal<double>(rad2deg<double>(entry.omega_z),         0.038);
            CheckReal<double>(                entry.a_x,              0.00781);
            CheckReal<double>(                entry.a_y,             -0.00391);
            CheckReal<double>(                entry.a_z,              0.07031);
        }

        {
            const Entry &entry = data[1];
            CheckReal<double>(                entry.time,          2733.93);
            CheckReal<double>(rad2deg<double>(entry.longitude),      15.755531608);
            CheckReal<double>(rad2deg<double>(entry.latitude),       42.900354289);
            CheckReal<double>(                entry.altitude,      3657.4);
            CheckReal<double>(rad2deg<double>(entry.true_heading),  178.9);
            CheckReal<double>(rad2deg<double>(entry.pitch),           0.2);
            CheckReal<double>(rad2deg<double>(entry.roll),           -0.4);
            CheckReal<double>(                entry.v_x,            169.2);
            CheckReal<double>(                entry.v_y,             -1.0);
            CheckReal<double>(                entry.v_z,              0.7);
            CheckReal<double>(rad2deg<double>(entry.omega_x),        -0.032);
            CheckReal<double>(rad2deg<double>(entry.omega_y),         0.010);
            CheckReal<double>(rad2deg<double>(entry.omega_z),         0.039);
            CheckReal<double>(                entry.a_x,              0.00781);
            CheckReal<double>(                entry.a_y,             -0.00391);
            CheckReal<double>(                entry.a_z,              0.06641);
        }
    }
}
