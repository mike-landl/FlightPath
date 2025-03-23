#pragma once

namespace FlightData
{
    template <typename REAL>
    struct Vec3
    {
        REAL x;
        REAL y;
        REAL z;

        auto inline operator+(const Vec3 &other) -> Vec3;
        auto inline operator-(const Vec3 &other) -> Vec3;
        auto inline operator*(const REAL scalar) -> Vec3;
        auto inline Dot(const Vec3 &other) -> REAL;
        auto inline Cross(const Vec3 &other) -> Vec3;
    };
}
