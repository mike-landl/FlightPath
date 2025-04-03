#pragma once

#include <cmath>

namespace FlightPath
{
    /**
     * @struct Vec3
     * @brief A lightweight 3D vector struct for basic vector operations.
     *
     * @tparam REAL The real type (i.e. float or double) used for storage and operations.
     */
    template <typename REAL>
    struct Vec3
    {
        REAL x; ///< The x-component of the vector.
        REAL y; ///< The y-component of the vector.
        REAL z; ///< The z-component of the vector.

        /**
         * @brief Adds two vectors component-wise.
         * @param other The vector to add.
         * @return The resulting vector after addition.
         */
        auto inline operator + (const Vec3 &other) const -> Vec3;

        /**
         * @brief Subtracts another vector from this vector component-wise.
         * @param other The vector to subtract.
         * @return The resulting vector after subtraction.
         */
        auto inline operator - (const Vec3 &other) const -> Vec3;

        /**
         * @brief Multiplies this vector by a scalar.
         * @param scalar The scalar value to multiply by.
         * @return The resulting scaled vector.
         */
        auto inline operator * (const REAL scalar) const -> Vec3;

        /**
         * @brief Computes the dot product of this vector and another.
         * @param other The other vector.
         * @return The dot product (a scalar).
         */
        auto inline Dot(const Vec3 &other) const -> REAL;

        /**
         * @brief Computes the cross product of this vector and another.
         * @param other The other vector.
         * @return The resulting vector perpendicular to both.
         */
        auto inline Cross(const Vec3 &other) const -> Vec3;

        /**
         * @brief Computes the Euclidean length (magnitude) of the vector.
         * @return The length as a scalar.
         */
        auto inline Length() const -> REAL;

        /**
         * @brief Computes the squared length of the vector.
         * @return The squared length (avoids square root for performance).
         */
        auto inline LengthSquared() const -> REAL;

        /**
         * @brief Normalizes the vector in-place to unit length.
         */
        auto inline Normalize() -> void;

        /**
         * @brief Returns a normalized (unit length) copy of the vector.
         * @return A normalized vector.
         */
        auto inline Normalized() const -> Vec3;
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
    auto inline Vec3<REAL>::Dot(const Vec3<REAL> &other) const -> REAL
    {
        const auto a1 = this->x; const auto b1 = other.x;
        const auto a2 = this->y; const auto b2 = other.y;
        const auto a3 = this->z; const auto b3 = other.z;

        return a1*b1 + a2*b2 + a3*b3;
    }

    template <typename REAL>
    auto inline Vec3<REAL>::Cross(const Vec3<REAL> &other) const -> Vec3<REAL>
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

    template <typename REAL>
    auto inline Vec3<REAL>::Length() const -> REAL
    {
        return std::sqrt(this->Dot((*this)));
    }

    template <typename REAL>
    auto inline Vec3<REAL>::LengthSquared() const -> REAL
    {
        return this->Dot((*this));
    }

    template <typename REAL>
    auto inline Vec3<REAL>::Normalize() -> void
    {
        const REAL inverse_length = 1.0 / this->Length();
        (*this) = (*this) * inverse_length;
    }

    template <typename REAL>
    auto inline Vec3<REAL>::Normalized() const -> Vec3<REAL>
    {
        const REAL inverse_length = 1.0 / this->Length();
        return (*this) * inverse_length;
    }
}
