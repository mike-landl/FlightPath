#include "ReferenceFrame.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

namespace FlightPath
{
    static auto CheckDouble(const double value, const double expected, const double factor) -> void
    {
        REQUIRE_THAT(
            value,
            Catch::Matchers::WithinRel(
                expected,
                factor * std::numeric_limits<double>::epsilon()
            )
        );
    }

    TEST_CASE("[ReferenceFrame] Set Get Position Roundtrip", "[ReferenceFrame]")
    {
        Position initial_position{
            .longitude =    15.34359762_deg,
            .latitude  =    46.80092545_deg,
            .altitude  = 3'902.4_m,
        };

        ReferenceFrame ref_frame(initial_position);

        Position position = ref_frame.GetPosition();
        CheckDouble(position.longitude, initial_position.longitude, 1);
        CheckDouble(position.latitude,  initial_position.latitude , 1);
        CheckDouble(position.altitude,  initial_position.altitude , 1000);

        //ref_frame.PrintPosition();
        //ref_frame.PrintAttitude();
    }

    TEST_CASE("[ReferenceFrame] Set Attitude", "[ReferenceFrame]")
    {
        constexpr double heading = 280.0_deg;
        constexpr double pitch   =  -2.0_deg;
        constexpr double roll    =  15.0_deg;

        ReferenceFrame ref_frame;
        
        ref_frame.SetAttitude(Attitude{.heading=heading, .pitch=pitch, .roll=roll});
        Attitude attitude = ref_frame.GetAttitude();
        //ref_frame.PrintAttitude(attitude);

        CheckDouble(attitude.heading, heading, 1);
        CheckDouble(attitude.pitch,   pitch,   1);
        CheckDouble(attitude.roll,    roll,    1);
    }

    TEST_CASE("[ReferenceFrame] Attitude does not influence position", "[ReferenceFrame]")
    {
        Position initial_position{
            .longitude = 15.34359762_deg,
            .latitude  = 46.80092545_deg,
            .altitude = 3902.4_m,
        };

        constexpr double heading = 280.0_deg;
        constexpr double pitch   =  -2.0_deg;
        constexpr double roll    =  15.0_deg;

        ReferenceFrame ref_frame(initial_position);

        // Rotate COG to body fixed system heading -> pitch -> roll
        ref_frame.GetAttitude();
        ref_frame.RotateZ(heading);
        ref_frame.RotateY(pitch);
        ref_frame.RotateX(roll);

        Position position = ref_frame.GetPosition();
        CheckDouble(position.longitude, initial_position.longitude, 1);
        CheckDouble(position.latitude,  initial_position.latitude , 1);
        CheckDouble(position.altitude,  initial_position.altitude , 1000);

        //ref_frame.PrintPosition();
        //ref_frame.PrintAttitude();
    }

    TEST_CASE("[ReferenceFrame] Orthonormalization", "[ReferenceFrame]")
    {
        ReferenceFrame transform(Mat4<double>{
            1.00,  0.10, 0.00, 0.0,
            0.00,  0.90, 0.20, 0.0,
            0.10, -0.10, 0.95, 0.0,
            0.00,  0.00, 0.00, 1.0
        });
        //Log::Info("{} {}", transform.GetOrthogonalError(), transform.GetLengthError());
        transform.Orthonormalize();
        //Log::Info("{} {}", transform.GetOrthogonalError(), transform.GetLengthError());
        
        REQUIRE(transform.GetOrthogonalError() < 1e-9);
        REQUIRE(transform.GetLengthError() < 1e-6);
    }
}