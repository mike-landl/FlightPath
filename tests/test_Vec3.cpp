#include "Vec3.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

namespace FlightPath
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

    TEST_CASE("[Vec3] add", "[Vec3]")
    {
        Vec3<double> a{.x=1.0, .y=2.0, .z= 3.0};
        Vec3<double> b{.x=1.0, .y=5.0, .z=-1.0};

        auto c = a + b;

        CheckVec3(c, Vec3<double>(2.0, 7.0, 2.0));
    }

    TEST_CASE("[Vec3] subtract", "[Vec3]")
    {
        Vec3<double> a{.x=1.0, .y=2.0, .z= 3.0};
        Vec3<double> b{.x=1.0, .y=5.0, .z=-1.0};

        auto c = a - b;

        CheckVec3(c, Vec3<double>(0.0, -3.0, 4.0));
    }

    TEST_CASE("[Vec3] scalar product", "[Vec3]")
    {
        Vec3<double> a{.x=1.0, .y=2.0, .z=3.0};

        auto c = a * 5.0;

        CheckVec3(c, Vec3<double>(5.0, 10.0, 15.0));
    }

    TEST_CASE("[Vec3] dot product", "[Vec3]")
    {
        Vec3<double> a{.x=1.0, .y=2.0, .z= 3.0};
        Vec3<double> b{.x=1.0, .y=5.0, .z=-1.0};

        auto c = a.Dot(b);

        CheckDouble(c, 8.0);
    }

    TEST_CASE("[Vec3] cross product", "[Vec3]")
    {
        Vec3<double> a{.x=1.0, .y=2.0, .z= 3.0};
        Vec3<double> b{.x=1.0, .y=5.0, .z=-1.0};

        auto c = a.Cross(b);

        CheckVec3(c, Vec3<double>(-17.0, 4.0, 3.0));
    }

    TEST_CASE("[Vec3] length", "[Vec3]")
    {
        {
            Vec3<double> a{.x=2.0, .y=0.0, .z=0.0};
            CheckDouble(a.Length(), 2.0);
        }

        {
            Vec3<double> a{.x=1.0, .y=1.0, .z=1.0};
            CheckDouble(a.Length(), std::sqrt(3.0));
        }
    }

    TEST_CASE("[Vec3] length squared", "[Vec3]")
    {
        {
            Vec3<double> a{.x=2.0, .y=0.0, .z=0.0};
            a.Normalize();
            CheckVec3(a, Vec3<double>(1.0, 0.0, 0.0));
        }

        {
            Vec3<double> a{.x=2.0, .y=1.0, .z=1.0};
            a.Normalize();
            CheckDouble(a.Length(), 1.0);
        }
    }

    TEST_CASE("[Vec3] normalize (inline)", "[Vec3]")
    {
        {
            Vec3<double> a{.x=2.0, .y=0.0, .z=0.0};
            a.Normalize();
            CheckVec3(a, Vec3<double>(1.0, 0.0, 0.0));
        }

        {
            Vec3<double> a{.x=2.0, .y=1.0, .z=1.0};
            a.Normalize();
            CheckDouble(a.Length(), 1.0);
        }
    }

    TEST_CASE("[Vec3] normalized (const)", "[Vec3]")
    {
        {
            Vec3<double> a{.x=2.0, .y=0.0, .z=0.0};
            auto b = a.Normalized();
            CheckVec3(b, Vec3<double>(1.0, 0.0, 0.0));
        }

        {
            Vec3<double> a{.x=2.0, .y=1.0, .z=1.0};
            auto b = a.Normalized();
            CheckDouble(b.Length(), 1.0);
        }
    }
}