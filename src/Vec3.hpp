#pragma once

namespace FlightData
{
    template <typename REAL>
    struct Vec3
    {
        REAL x;
        REAL y;
        REAL z;

        auto inline operator + (const Vec3 &other) const -> Vec3;
        auto inline operator - (const Vec3 &other) const -> Vec3;
        auto inline operator * (const REAL scalar) const -> Vec3;
        auto inline Dot(const Vec3 &other) -> REAL;
        auto inline Cross(const Vec3 &other) -> Vec3;
    };

template <typename REAL>
    auto inline Vec3<REAL>::operator + (const Vec3 &other) const -> Vec3<REAL>
    {
        return Vec3<REAL>{
            .x = (this->x + other.x),
            .y = (this->y + other.y),
            .z = (this->z + other.z)
        };
    }

    template <typename REAL>
    auto inline Vec3<REAL>::operator - (const Vec3<REAL> &other) const -> Vec3<REAL>
    {
        return Vec3<REAL>{
            .x = (this->x - other.x),
            .y = (this->y - other.y),
            .z = (this->z - other.z)
        };
    }

    template <typename REAL>
    auto inline Vec3<REAL>::operator * (const REAL scalar) const -> Vec3<REAL>
    {
        return Vec3<REAL>{
            .x = (this->x * scalar),
            .y = (this->y * scalar),
            .z = (this->z * scalar)
        };
    }

    template <typename REAL>
    auto inline operator * (const double scalar, const Vec3<REAL>& v) -> Vec3<REAL>
    {
        return v * scalar;
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
}
