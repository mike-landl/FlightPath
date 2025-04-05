#include "ReferenceFrame.hpp"
#include "TestHelper.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

namespace FlightPath
{
    TEST_CASE("[ReferenceFrame] Set Get Position Roundtrip", "[ReferenceFrame]")
    {
        Position initial_position{
            .longitude =    15.34359762_deg,
            .latitude  =    46.80092545_deg,
            .altitude  = 3'902.4_m,
        };

        ReferenceFrame ref_frame(initial_position);

        Position position = ref_frame.GetPosition();
        CheckReal<double>(position.longitude, initial_position.longitude, 1);
        CheckReal<double>(position.latitude,  initial_position.latitude , 1);
        CheckReal<double>(position.altitude,  initial_position.altitude , 1000);

        //ref_frame.PrintPosition();
        //ref_frame.PrintAttitude();
    }

    TEST_CASE("[ReferenceFrame] Print Position works", "[ReferenceFrame]")
    {
        Position initial_position{
            .longitude =    15.34359762_deg,
            .latitude  =    46.80092545_deg,
            .altitude  = 3'902.4_m,
        };

        ReferenceFrame ref_frame(initial_position);
        // lambda for passing anonymous inline function to CaptureOutput
        auto console_output = CaptureOutput([ref_frame](){ref_frame.PrintPosition();});
        REQUIRE(console_output == "\x1B[92m[I]\x1B[0m Longitude 15.343598 deg Latitude 46.800925 deg Altitude 3902.40 m\n");
    }

    TEST_CASE("[ReferenceFrame] Set Get Attitude Roundtrip", "[ReferenceFrame]")
    {
        constexpr double heading = 280.0_deg;
        constexpr double pitch   =  -2.0_deg;
        constexpr double roll    =  15.0_deg;

        ReferenceFrame ref_frame;
        ref_frame.SetAttitude(Attitude{.heading=heading, .pitch=pitch, .roll=roll});

        // lambda for passing anonymous inline function to CaptureOutput
        auto console_output = CaptureOutput([ref_frame](){ref_frame.PrintAttitude();});
        REQUIRE(console_output == "\x1B[92m[I]\x1B[0m Heading 280.00 deg, Pitch -2.00 deg, Roll 15.00 deg\n");
    }

    TEST_CASE("[ReferenceFrame] Print Attitude works", "[ReferenceFrame]")
    {
        constexpr double heading = 280.0_deg;
        constexpr double pitch   =  -2.0_deg;
        constexpr double roll    =  15.0_deg;

        ReferenceFrame ref_frame;
        
        ref_frame.SetAttitude(Attitude{.heading=heading, .pitch=pitch, .roll=roll});
        Attitude attitude = ref_frame.GetAttitude();
        ref_frame.PrintAttitude(attitude);
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
        CheckReal<double>(position.longitude, initial_position.longitude, 1);
        CheckReal<double>(position.latitude,  initial_position.latitude , 1);
        CheckReal<double>(position.altitude,  initial_position.altitude , 1000);

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

