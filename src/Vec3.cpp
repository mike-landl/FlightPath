#include "Vec3.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "Types.hpp"

namespace FlightData
{
    template <typename REAL>
    auto inline Vec3<REAL>::operator+(const Vec3 &other) -> Vec3<REAL>
    {
        return Vec3<REAL>{
            .x = (this->x + other.x),
            .y = (this->y + other.y),
            .z = (this->z + other.z)
        };
    }

    template <typename REAL>
    auto inline Vec3<REAL>::operator-(const Vec3<REAL> &other) -> Vec3<REAL>
    {
        return Vec3<REAL>{
            .x = (this->x - other.x),
            .y = (this->y - other.y),
            .z = (this->z - other.z)
        };
    }

    template <typename REAL>
    auto inline Vec3<REAL>::operator*(const REAL scalar) -> Vec3<REAL>
    {
        return Vec3<REAL>{
            .x = (this->x * scalar),
            .y = (this->y * scalar),
            .z = (this->z * scalar)
        };
    }

    template <typename REAL>
    auto inline Vec3<REAL>::Dot(const Vec3<REAL> &other) -> REAL
    {
        const auto a1 = this->x; const auto b1 = other.x;
        const auto a2 = this->y; const auto b2 = other.y;
        const auto a3 = this->z; const auto b3 = other.z;

        return a1*b1 + a2*b2 + a3*b3;
    }

    template <typename REAL>
    auto inline Vec3<REAL>::Cross(const Vec3<REAL> &other) -> Vec3<REAL>
    {
        const auto a1 = this->x; const auto b1 = other.x;
        const auto a2 = this->y; const auto b2 = other.y;
        const auto a3 = this->z; const auto b3 = other.z;

        return Vec3<REAL>{
            .x = a2*b3 - a3*b2,
            .y = a3*b1 - a1*b3,
            .z = a1*b2 - a2*b1
        };
    }

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