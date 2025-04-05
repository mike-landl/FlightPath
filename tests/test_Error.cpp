#include "Error.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("[Error] Ensure only throws on flase", "[Error]")
{
    REQUIRE_THROWS(FlightPath::Ensure(false, "Does  throw"));
    REQUIRE_NOTHROW(FlightPath::Ensure(true, "Does not throw"));
}

TEST_CASE("[Error] Ensure formatter works", "[Error]")
{
    int a = 1;
    int b = 0;
    REQUIRE_THROWS(FlightPath::Ensure(a==b, "a is not equal to b"));
    REQUIRE_THROWS_WITH(FlightPath::Ensure(a==b, "a is not equal to b: a = {}, b = {}", a, b), "a is not equal to b: a = 1, b = 0");
}