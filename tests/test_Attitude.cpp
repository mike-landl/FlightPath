#include "Attitude.hpp"
#include "Units.hpp"

#include <iostream>
#include <format>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("[Attitude] formatter works", "[Attitude]")
{
    FlightPath::Attitude attitude{.heading=20.0_deg, .pitch=4.0_deg, .roll=3.2_deg};

    auto attitude_string = std::format("{}", attitude);
    REQUIRE_THAT(attitude_string, Catch::Matchers::ContainsSubstring("Heading 20.00 deg"));
    REQUIRE_THAT(attitude_string, Catch::Matchers::ContainsSubstring("Pitch 4.00 deg"));
    REQUIRE_THAT(attitude_string, Catch::Matchers::ContainsSubstring("Roll 3.20 deg"));
}
