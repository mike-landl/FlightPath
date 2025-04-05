#include "Position.hpp"
#include "Units.hpp"

#include <iostream>
#include <format>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("[Position] formatter works", "[Position]")
{
    FlightPath::Position position{
        .longitude =    15.0_deg,
        .latitude  =    46.8_deg,
        .altitude  = 3'902.4_m,
    };

    auto position_string = std::format("{}", position);
    REQUIRE_THAT(position_string, Catch::Matchers::ContainsSubstring("Longitude 15.000000 deg"));
    REQUIRE_THAT(position_string, Catch::Matchers::ContainsSubstring("Latitude 46.800000 deg"));
    REQUIRE_THAT(position_string, Catch::Matchers::ContainsSubstring("Altitude 3902.40 m"));
}
