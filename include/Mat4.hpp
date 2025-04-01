#pragma once

#include <array>
#include <iostream>
#include <format>

#include "Error.hpp"
#include "Types.hpp"
#include "Vec3.hpp"

namespace FlightData
{
    /**
     * @brief A 4x4 matrix class for 3D mathematical operations.
     * 
     * This class provides basic functionality for manipulating 4x4 matrices,
     * including addition, subtraction, scalar multiplication, and matrix multiplication.
     * It supports column operations and provides access to raw data.
     * 
     * @tparam REAL Floating-point type (e.g., float or double)
     */
    template <typename REAL>
    class Mat4
    {
    public:
        /** @brief Default constructor. Initializes the matrix with uninitialized data. */
        Mat4() = default;

        /**
         * @brief Construct a matrix from an initializer list.
         * 
         * @param values A list of 16 values in row-major order.
         * @throws FlightData::Exception if the list size is not 16.
         */
        Mat4(std::initializer_list<REAL> values)
        { 
            Ensure(values.size() == elements_, "Error: Length of initializer list does not match matrix dimensions!");

            std::copy(values.begin(), values.end(), data_.begin());
        };

        /** @brief Default destructor. */
        ~Mat4() = default;

        /**
         * @brief Sets the matrix values from an initializer list.
         * 
         * @param values A list of 16 values in row-major order.
         */
        auto SetMatrix(std::initializer_list<REAL> values) -> void
        {
            std::copy(values.begin(), values.end(), data_.begin());
        }

        /**
         * @brief Sets a specific column of the matrix using a Vec3.
         * 
         * @param col Index of the column to set (0-based).
         * @param v The 3D vector to assign to the column (last row remains unchanged).
         */
        auto inline SetColumn(const i32 col, const Vec3<REAL> &v) -> void;

        /**
         * @brief Retrieves a specific column of the matrix as a Vec3.
         * 
         * @param col Index of the column to retrieve (0-based).
         * @return A Vec3 containing the first 3 elements of the specified column.
         */
        auto inline GetColumn(const i32 col) const -> Vec3<REAL>;

        /** 
         * @brief Element access operator (mutable).
         * 
         * @param row Row index (0-based).
         * @param col Column index (0-based).
         * @return Reference to the element at (row, col).
         */
        auto inline operator()(size_t row, size_t col) -> REAL& { return data_[row * cols_ + col]; }

        /** 
         * @brief Element access operator (const).
         * 
         * @param row Row index (0-based).
         * @param col Column index (0-based).
         * @return Const reference to the element at (row, col).
         */
        auto inline operator()(size_t row, size_t col) const -> const REAL& { return data_[row * cols_ + col]; }

        /**
         * @brief Matrix addition.
         * 
         * @param other The matrix to add.
         * @return A new matrix containing the sum.
         */
        auto inline operator + (const Mat4<REAL>& other) const -> Mat4<REAL>;

        /**
         * @brief Matrix subtraction.
         * 
         * @param other The matrix to subtract.
         * @return A new matrix containing the difference.
         */
        auto inline operator - (const Mat4<REAL>& other) const -> Mat4<REAL>;

        /**
         * @brief Matrix-matrix multiplication.
         * 
         * @param B The right-hand side matrix.
         * @return A new matrix containing the product.
         */
        auto inline operator * (const Mat4<REAL>& B) const -> Mat4<REAL>;  

        /**
         * @brief Matrix-scalar multiplication.
         * 
         * @param scalar The scalar value to multiply by.
         * @return A new matrix with all elements multiplied by scalar.
         */
        auto inline operator * (const REAL scalar) const -> Mat4<REAL>;
        
        /**
         * @brief Prints the matrix to std::cout with a custom label.
         * 
         * @param label A label string printed before the matrix.
         */
        auto DebugPrint(std::string label) -> void;

        /**
         * @brief Prints the matrix to std::cout.
         * 
         * Outputs each row in formatted style.
         */
        auto DebugPrint() const -> void;

        /**
         * @brief Returns a raw pointer to the underlying matrix data (mutable).
         * 
         * @return Pointer to the beginning of the data array.
         */
        auto inline RawPtr() -> REAL* { return data_.data(); }
        
        /**
         * @brief Returns a raw pointer to the underlying matrix data (const).
         * 
         * @return Const pointer to the beginning of the data array.
         */
        auto inline RawPtr() const -> const REAL* { return data_.data(); }

        /**
         * @brief Gets the number of matrix rows.
         * @return Always returns 4.
         */
        constexpr auto inline rows() const -> size_t { return rows_; }

        /**
         * @brief Gets the number of matrix columns.
         * @return Always returns 4.
         */
        constexpr auto inline cols() const -> size_t { return cols_; }

        /**
         * @brief Gets the total number of matrix elements.
         * @return Always returns 16.
         */
        constexpr auto inline elements() const -> size_t { return elements_; }

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
