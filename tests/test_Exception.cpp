#include "Exception.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("[Exception] Behaves like a runtime_error", "[Exception]")
{
    REQUIRE_THROWS_AS([]{throw FlightPath::Exception("Test error");}(), FlightPath::Exception);
    REQUIRE_THROWS_AS([]{throw FlightPath::Exception("Test error");}(), std::runtime_error);
    REQUIRE_THROWS_WITH([]{throw FlightPath::Exception("Test error");}(), "Test error");
}
