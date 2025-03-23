#include "Units.hpp"

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

    TEST_CASE("[units] km literal", "[units]")
    {
        CheckDouble(-0.88973_km, -889.73);
        CheckDouble( 1.0_km,     1000.0 );
        CheckDouble( 2.45589_km, 2455.89);
    }

    TEST_CASE("[units] m literal", "[units]")
    {
        CheckDouble(   -0.54690_m,    -0.54690);
        CheckDouble(    1.0_m,         1.0    );
        CheckDouble(46657.0_m,     46657.0    );
    }

    TEST_CASE("[units] mm literal", "[units]")
    {
        CheckDouble(   -0.00468_mm, -0.00000468);
        CheckDouble(    1.0_mm,      0.001     );
        CheckDouble(45668.0_mm,     45.668     );
    }

    TEST_CASE("[units] feet literal", "[units]")
    {
        CheckDouble(   -0.00468_ft, -0.001426464);
        CheckDouble(    1.0_ft,      0.3048     );
        CheckDouble(45668.0_ft,     13919.6064  );
    }

    TEST_CASE("[units] meter to feet conversion", "[units]")
    {
        CheckDouble(m2ft(-0.001426464),    -0.00468);
        CheckDouble(m2ft( 0.3048     ),     1.0    );
        CheckDouble(m2ft(13919.6064  ), 45668.0    );
    }

    TEST_CASE("[units] degree literal", "[units]")
    {
        CheckDouble(  0.0_deg, 0.0/4.0*PI_d);
        CheckDouble( 45.0_deg, 1.0/4.0*PI_d);
        CheckDouble( 90.0_deg, 2.0/4.0*PI_d);
        CheckDouble(135.0_deg, 3.0/4.0*PI_d);
        CheckDouble(180.0_deg, 4.0/4.0*PI_d);
        CheckDouble(225.0_deg, 5.0/4.0*PI_d);
        CheckDouble(270.0_deg, 6.0/4.0*PI_d);
        CheckDouble(315.0_deg, 7.0/4.0*PI_d);
        CheckDouble(360.0_deg, 8.0/4.0*PI_d);
    }

    TEST_CASE("[units] radian to degrees conversion", "[units]")
    {
        CheckDouble(rad2deg(0.0/4.0*PI_d),   0.0);
        CheckDouble(rad2deg(1.0/4.0*PI_d),  45.0);
        CheckDouble(rad2deg(2.0/4.0*PI_d),  90.0);
        CheckDouble(rad2deg(3.0/4.0*PI_d), 135.0);
        CheckDouble(rad2deg(4.0/4.0*PI_d), 180.0);
        CheckDouble(rad2deg(5.0/4.0*PI_d), 225.0);
        CheckDouble(rad2deg(6.0/4.0*PI_d), 270.0);
        CheckDouble(rad2deg(7.0/4.0*PI_d), 315.0);
        CheckDouble(rad2deg(8.0/4.0*PI_d), 360.0);
    }
}
