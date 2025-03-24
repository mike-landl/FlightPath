#pragma once

#include <array>
#include <iostream>
#include <format>

#include "Error.hpp"
#include "Types.hpp"
#include "Vec3.hpp"

namespace FlightData
{
    template <typename REAL>
    class Mat4
    {
    public:
        Mat4() = default;

        Mat4(std::initializer_list<REAL> values)
        { 
            Ensure(values.size() == elements_, "Error: Length of initializer list does not match matrix dimensions!");

            std::copy(values.begin(), values.end(), data_.begin());
        };

        ~Mat4() = default;

        auto SetMatrix(std::initializer_list<REAL> values) -> void
        {
            std::copy(values.begin(), values.end(), data_.begin());
        }

        auto inline SetColumn(const i32 col, const Vec3<REAL> &v)       -> void;
        auto inline GetColumn(const i32 col                     ) const -> Vec3<REAL>;

    /* Operator overloading */

              REAL& operator()(size_t row, size_t col)       { return data_[row * cols_ + col]; }
        const REAL& operator()(size_t row, size_t col) const { return data_[row * cols_ + col]; }

        auto inline operator + (const Mat4<REAL>& other) const -> Mat4<REAL>;
        auto inline operator - (const Mat4<REAL>& other) const -> Mat4<REAL>;

        auto inline operator * (const Mat4<REAL>& B) const -> Mat4<REAL>; // Matrix Matrix Product        
        auto inline operator * (const REAL scalar)   const -> Mat4<REAL>; // Matrix Scalar Product
        
        auto DebugPrint(std::string label) -> void;
        auto DebugPrint() const -> void;

        // getters for private members
        auto inline RawPtr()       ->       REAL* { return data_.data(); }
        auto inline RawPtr() const -> const REAL* { return data_.data(); }

        auto inline rows()     const -> size_t { return rows_; }
        auto inline cols()     const -> size_t { return cols_; }
        auto inline elements() const -> size_t { return elements_; }

    private:
        std::array<REAL, 16> data_;
        static constexpr size_t rows_ = 4;
        static constexpr size_t cols_ = 4;
        static constexpr size_t elements_ = 16;
    };

    template <typename REAL>
    auto inline Mat4<REAL>::operator + (const Mat4<REAL>& other) const -> Mat4<REAL>
    {
        Mat4<REAL> C;

        for (size_t row = 0; row < rows_; ++row)
        {
            const double Ai0 = (*this)(row, 0); const double Bi0 = other(row, 0);
            const double Ai1 = (*this)(row, 1); const double Bi1 = other(row, 1);
            const double Ai2 = (*this)(row, 2); const double Bi2 = other(row, 2);
            const double Ai3 = (*this)(row, 3); const double Bi3 = other(row, 3);

            C(row, 0) = Ai0 + Bi0;
            C(row, 1) = Ai1 + Bi1;
            C(row, 2) = Ai2 + Bi2;
            C(row, 3) = Ai3 + Bi3;
        }
        
        return C;
    }

    template <typename REAL>
    auto inline Mat4<REAL>::operator - (const Mat4<REAL>& other) const -> Mat4<REAL>
    {
        Mat4<REAL> C;

        for (size_t row = 0; row < rows_; ++row)
        {
            const double Ai0 = (*this)(row, 0); const double Bi0 = other(row, 0);
            const double Ai1 = (*this)(row, 1); const double Bi1 = other(row, 1);
            const double Ai2 = (*this)(row, 2); const double Bi2 = other(row, 2);
            const double Ai3 = (*this)(row, 3); const double Bi3 = other(row, 3);

            C(row, 0) = Ai0 - Bi0;
            C(row, 1) = Ai1 - Bi1;
            C(row, 2) = Ai2 - Bi2;
            C(row, 3) = Ai3 - Bi3;
        }
        
        return C;
    }

    template <typename REAL>
    auto inline Mat4<REAL>::operator * (const REAL scalar) const -> Mat4<REAL>
    {
        Mat4<REAL> C;

        for (size_t i = 0; i < rows_; ++i)
        {
            const double Ai0 = (*this)(i, 0);
            const double Ai1 = (*this)(i, 1);
            const double Ai2 = (*this)(i, 2);
            const double Ai3 = (*this)(i, 3);

            C(i, 0) = Ai0 * scalar;
            C(i, 1) = Ai1 * scalar;
            C(i, 2) = Ai2 * scalar;
            C(i, 3) = Ai3 * scalar;
        }

        return C;
    }

    template <typename REAL>
    auto Mat4<REAL>::operator * (const Mat4<REAL>& B) const -> Mat4<REAL>
    {
        Mat4<REAL> C;

        for (size_t i = 0; i < rows_; ++i)
        {
            const double Ai0 = (*this)(i, 0);
            const double Ai1 = (*this)(i, 1);
            const double Ai2 = (*this)(i, 2);
            const double Ai3 = (*this)(i, 3);

            C(i, 0) = Ai0 * B(0, 0) + Ai1 * B(1, 0) + Ai2 * B(2, 0) + Ai3 * B(3, 0);
            C(i, 1) = Ai0 * B(0, 1) + Ai1 * B(1, 1) + Ai2 * B(2, 1) + Ai3 * B(3, 1);
            C(i, 2) = Ai0 * B(0, 2) + Ai1 * B(1, 2) + Ai2 * B(2, 2) + Ai3 * B(3, 2);
            C(i, 3) = Ai0 * B(0, 3) + Ai1 * B(1, 3) + Ai2 * B(2, 3) + Ai3 * B(3, 3);
        }

        return C;
    }

    template <typename REAL>
    auto Mat4<REAL>::SetColumn(const i32 col, const Vec3<REAL> &v) -> void
    {
        (*this)(0, col) = v.x;
        (*this)(1, col) = v.y;
        (*this)(2, col) = v.z;
    }

    template <typename REAL>
    auto Mat4<REAL>::GetColumn(const i32 col) const -> Vec3<REAL>
    {
        return Vec3<REAL>{
            .x = (*this)(0, col), 
            .y = (*this)(1, col), 
            .z = (*this)(2, col)
        };
    }

    template <typename REAL>
    auto Mat4<REAL>::DebugPrint(std::string label) -> void
    {
        std::cout << label << "\n" << std::endl;
        DebugPrint();
    }

    template <typename REAL>
    auto Mat4<REAL>::DebugPrint() const -> void
    {
        for (size_t row = 0; row < rows_; ++row)
        {
            std::cout << std::format(" {:12.4f}", (*this)(row, 0));
            for (size_t col = 1; col < cols_; ++col)
            {
                std::cout << std::format(" {:12.4f}", (*this)(row, col));
            }
            std::cout << "\n";
        }
    }
}
