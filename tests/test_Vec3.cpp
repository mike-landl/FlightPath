#include "Vec3.hpp"
#include "TestHelper.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

namespace FlightPath
{
    TEMPLATE_TEST_CASE("[Vec3] add", "[Vec3]", float, double)
    {
        Vec3<TestType> a{.x=1.0, .y=2.0, .z= 3.0};
        Vec3<TestType> b{.x=1.0, .y=5.0, .z=-1.0};

        auto c = a + b;

        CheckVec3<TestType>(c, Vec3<TestType>(2.0, 7.0, 2.0));
    }

    TEMPLATE_TEST_CASE("[Vec3] subtract", "[Vec3]", float, double)
    {
        Vec3<TestType> a{.x=1.0, .y=2.0, .z= 3.0};
        Vec3<TestType> b{.x=1.0, .y=5.0, .z=-1.0};

        auto c = a - b;

        CheckVec3<TestType>(c, Vec3<TestType>(0.0, -3.0, 4.0));
    }

    TEMPLATE_TEST_CASE("[Vec3] scalar product", "[Vec3]", float, double)
    {
        Vec3<TestType> a{.x=1.0, .y=2.0, .z=3.0};

        auto c = a * 5.0;

        CheckVec3<TestType>(c, Vec3<TestType>(5.0, 10.0, 15.0));
    }

    TEMPLATE_TEST_CASE("[Vec3] dot product", "[Vec3]", float, double)
    {
        Vec3<TestType> a{.x=1.0, .y=2.0, .z= 3.0};
        Vec3<TestType> b{.x=1.0, .y=5.0, .z=-1.0};

        auto c = a.Dot(b);

        CheckReal<TestType>(c, 8.0);
    }

    TEMPLATE_TEST_CASE("[Vec3] cross product", "[Vec3]", float, double)
    {
        Vec3<TestType> a{.x=1.0, .y=2.0, .z= 3.0};
        Vec3<TestType> b{.x=1.0, .y=5.0, .z=-1.0};

        auto c = a.Cross(b);

        CheckVec3<TestType>(c, Vec3<TestType>(-17.0, 4.0, 3.0));
    }

    TEMPLATE_TEST_CASE("[Vec3] length", "[Vec3]", float, double)
    {
        {
            Vec3<TestType> a{.x=2.0, .y=0.0, .z=0.0};
            CheckReal<TestType>(a.Length(), 2.0);
        }

        {
            Vec3<TestType> a{.x=1.0, .y=1.0, .z=1.0};
            CheckReal<TestType>(a.Length(), std::sqrt(TestType(3.0)));
        }
    }

    TEMPLATE_TEST_CASE("[Vec3] length squared", "[Vec3]", float, double)
    {
        {
            Vec3<TestType> a{.x=2.0, .y=0.0, .z=0.0};
            a.Normalize();
            CheckVec3<TestType>(a, Vec3<TestType>(1.0, 0.0, 0.0));
        }

        {
            Vec3<TestType> a{.x=2.0, .y=1.0, .z=1.0};
            a.Normalize();
            CheckReal<TestType>(a.Length(), 1.0);
        }
    }

    TEMPLATE_TEST_CASE("[Vec3] normalize (inline)", "[Vec3]", float, double)
    {
        {
            Vec3<TestType> a{.x=2.0, .y=0.0, .z=0.0};
            a.Normalize();
            CheckVec3<TestType>(a, Vec3<TestType>(1.0, 0.0, 0.0));
        }

        {
            Vec3<TestType> a{.x=2.0, .y=1.0, .z=1.0};
            a.Normalize();
            CheckReal<TestType>(a.Length(), 1.0);
        }
    }

    TEMPLATE_TEST_CASE("[Vec3] normalized (const)", "[Vec3]", float, double)
    {
        {
            Vec3<TestType> a{.x=2.0, .y=0.0, .z=0.0};
            auto b = a.Normalized();
            CheckVec3<TestType>(b, Vec3<TestType>(1.0, 0.0, 0.0));
        }

        {
            Vec3<TestType> a{.x=2.0, .y=1.0, .z=1.0};
            auto b = a.Normalized();
            CheckReal<TestType>(b.Length(), 1.0);
        }
    }
}