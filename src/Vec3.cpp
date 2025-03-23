#include "Vec3.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "Types.hpp"

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

    static auto CheckVec3(const Vec3<double> &actual, const Vec3<double> &expected) -> void
    {
        CheckDouble(actual.x, expected.x);
        CheckDouble(actual.y, expected.y);
        CheckDouble(actual.z, expected.z);
    }

    TEST_CASE("[vec3] add", "[vec3]")
    {
        Vec3<double> a{.x=1, .y=2, .z= 3};
        Vec3<double> b{.x=1, .y=5, .z=-1};

        auto c = a + b;

        CheckVec3(c, Vec3<double>(2, 7, 2));
    }

    TEST_CASE("[vec3] subtract", "[vec3]")
    {
        Vec3<double> a{.x=1, .y=2, .z= 3};
        Vec3<double> b{.x=1, .y=5, .z=-1};

        auto c = a - b;

        CheckVec3(c, Vec3<double>(0, -3, 4));
    }

    TEST_CASE("[vec3] scalar product", "[vec3]")
    {
        Vec3<double> a{.x=1, .y=2, .z=3};

        auto c = a * 5;

        CheckVec3(c, Vec3<double>(5, 10, 15));
    }

    TEST_CASE("[vec3] dot product", "[vec3]")
    {
        Vec3<double> a{.x=1, .y=2, .z= 3};
        Vec3<double> b{.x=1, .y=5, .z=-1};

        auto c = a.Dot(b);

        CheckDouble(c, 8);
    }

    TEST_CASE("[vec3] cross product", "[vec3]")
    {
        Vec3<double> a{.x=1, .y=2, .z= 3};
        Vec3<double> b{.x=1, .y=5, .z=-1};

        auto c = a.Cross(b);

        CheckVec3(c, Vec3<double>(-17, 4, 3));
    }
}