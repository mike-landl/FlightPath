#include "Units.hpp"
#include "TestHelper.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

namespace FlightPath
{
    TEST_CASE("[Units] km literal", "[Units]")
    {
        CheckReal<double>(-0.88973_km, -889.73);
        CheckReal<double>( 1.0_km,     1000.0 );
        CheckReal<double>( 2.45589_km, 2455.89);
    }

    TEST_CASE("[Units] m literal", "[Units]")
    {
        CheckReal<double>(   -0.54690_m,    -0.54690);
        CheckReal<double>(    1.0_m,         1.0    );
        CheckReal<double>(46657.0_m,     46657.0    );
    }

    TEST_CASE("[Units] mm literal", "[Units]")
    {
        CheckReal<double>(   -0.00468_mm, -0.00000468);
        CheckReal<double>(    1.0_mm,      0.001     );
        CheckReal<double>(45668.0_mm,     45.668     );
    }

    TEST_CASE("[Units] feet literal", "[Units]")
    {
        CheckReal<double>(   -0.00468_ft, -0.001426464);
        CheckReal<double>(    1.0_ft,      0.3048     );
        CheckReal<double>(45668.0_ft,     13919.6064  );
    }

    TEST_CASE("[Units] meter to feet conversion", "[Units]")
    {
        CheckReal<double>(m2ft<double>(-0.001426464),    -0.00468);
        CheckReal<double>(m2ft<double>( 0.3048     ),     1.0    );
        CheckReal<double>(m2ft<double>(13919.6064  ), 45668.0    );
    }

    TEST_CASE("[Units] km float literal", "[Units]")
    {
        CheckReal<float>(-0.88973_km_f, -889.73f);
        CheckReal<float>( 1.0_km_f,     1000.0f );
        CheckReal<float>( 2.45589_km_f, 2455.89f);
    }

    TEST_CASE("[Units] m float literal", "[Units]")
    {
        CheckReal<float>(   -0.54690_m_f,    -0.54690f);
        CheckReal<float>(    1.0_m_f,         1.0f    );
        CheckReal<float>(46657.0_m_f,     46657.0f    );
    }

    TEST_CASE("[Units] mm float literal", "[Units]")
    {
        CheckReal<float>(   -0.00468_mm_f, -0.00000468f);
        CheckReal<float>(    1.0_mm_f,      0.001f     );
        CheckReal<float>(45668.0_mm_f,     45.668f     );
    }

    TEST_CASE("[Units] feet float literal", "[Units]")
    {
        CheckReal<float>(   -0.00468_ft_f, -0.001426464f);
        CheckReal<float>(    1.0_ft_f,      0.3048f     );
        CheckReal<float>(45668.0_ft_f,     13919.6064f  );
    }

    TEST_CASE("[Units] degree literal", "[Units]")
    {
        CheckReal<double>(  0.0_deg, 0.0/4.0*PI_d);
        CheckReal<double>( 45.0_deg, 1.0/4.0*PI_d);
        CheckReal<double>( 90.0_deg, 2.0/4.0*PI_d);
        CheckReal<double>(135.0_deg, 3.0/4.0*PI_d);
        CheckReal<double>(180.0_deg, 4.0/4.0*PI_d);
        CheckReal<double>(225.0_deg, 5.0/4.0*PI_d);
        CheckReal<double>(270.0_deg, 6.0/4.0*PI_d);
        CheckReal<double>(315.0_deg, 7.0/4.0*PI_d);
        CheckReal<double>(360.0_deg, 8.0/4.0*PI_d);
    }

    TEST_CASE("[Units] degree float literal", "[Units]")
    {
        CheckReal<float>(  0.0_deg_f, 0.0f/4.0f*PI_f);
        CheckReal<float>( 45.0_deg_f, 1.0f/4.0f*PI_f);
        CheckReal<float>( 90.0_deg_f, 2.0f/4.0f*PI_f);
        CheckReal<float>(135.0_deg_f, 3.0f/4.0f*PI_f);
        CheckReal<float>(180.0_deg_f, 4.0f/4.0f*PI_f);
        CheckReal<float>(225.0_deg_f, 5.0f/4.0f*PI_f);
        CheckReal<float>(270.0_deg_f, 6.0f/4.0f*PI_f);
        CheckReal<float>(315.0_deg_f, 7.0f/4.0f*PI_f);
        CheckReal<float>(360.0_deg_f, 8.0f/4.0f*PI_f);
    }

    TEST_CASE("[Units] radian to degrees conversion", "[Units]")
    {
        CheckReal<double>(rad2deg<double>(0.0/4.0*PI_d),   0.0);
        CheckReal<double>(rad2deg<double>(1.0/4.0*PI_d),  45.0);
        CheckReal<double>(rad2deg<double>(2.0/4.0*PI_d),  90.0);
        CheckReal<double>(rad2deg<double>(3.0/4.0*PI_d), 135.0);
        CheckReal<double>(rad2deg<double>(4.0/4.0*PI_d), 180.0);
        CheckReal<double>(rad2deg<double>(5.0/4.0*PI_d), 225.0);
        CheckReal<double>(rad2deg<double>(6.0/4.0*PI_d), 270.0);
        CheckReal<double>(rad2deg<double>(7.0/4.0*PI_d), 315.0);
        CheckReal<double>(rad2deg<double>(8.0/4.0*PI_d), 360.0);
    }

    TEST_CASE("[Units] templated PI gives correct values", "[Units]")
    {
        CheckReal<float>(PI<float>(),   3.1415927f);        //  7 digits
        CheckReal<double>(PI<double>(), 3.141592653589793); // 15 digits
        //CheckReal<long double>(PI<long double>(), 3.14l); Catch2 does not provide a overload for long double
    }

    TEST_CASE("[Units] templated 2 times PI gives correct values", "[Units]")
    {
        CheckReal<float>(TWO_PI<float>(),   6.2831853f);        //  7 digits
        CheckReal<double>(TWO_PI<double>(), 6.283185307179586); // 15 digits
        //CheckReal<long double>(PI<long double>(), 3.14l); Catch2 does not provide a overload for long double
    }

}
