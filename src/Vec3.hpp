#pragma once

namespace FlightData
{
    template <typename REAL>
    struct Vec3
    {
        REAL x, y, z;
        Vec3() : x(0), y(0), z(0) {};
        Vec3(REAL x, REAL y, REAL z) : x(x), y(y), z(z) {}
    };
}
