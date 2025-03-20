#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include <format>
#include <initializer_list>

#include "ColumnVector.hpp"
#include "Error.hpp"

namespace FlightData
{
    enum class MatrixLayout
    {
        RowMajor,
        ColumnMajor
    };

    // todo: add copy constructor and assignment?
    template <typename REAL, MatrixLayout LAYOUT>
    class Matrix
    {
    public:
        Matrix() = delete;
        ~Matrix() = default;

        Matrix(size_t rows, size_t cols)
        : rows_(rows)
        , cols_(cols)
        , elements_(rows*cols)
        , data_(rows*cols, REAL(0.0))
        { };

        // The initializer list is always supplied in RowMajor layout!
        auto SetMatrix(std::initializer_list<REAL> values) -> void;

        auto operator()(size_t row, size_t col)       ->       REAL&;
        auto operator()(size_t row, size_t col) const -> const REAL&;

        // Matrix Matrix Multiplication
        auto operator*(const Matrix<REAL, LAYOUT>& B) const -> Matrix<REAL, LAYOUT>;

        auto DebugPrint(std::string label) -> void;
        auto DebugPrint() const -> void;

        // getters for private members
        auto RawPtr()       ->       REAL* { return data_.data(); }
        auto RawPtr() const -> const REAL* { return data_.data(); }

        auto rows()     const -> size_t { return rows_; }
        auto cols()     const -> size_t { return cols_; }
        auto elements() const -> size_t { return elements_; }

    private:
        std::vector<REAL> data_;
        size_t rows_ = 0;
        size_t cols_ = 0;
        size_t elements_ = 0;
    };

    template <typename REAL, MatrixLayout LAYOUT>
    void Matrix<REAL, LAYOUT>::SetMatrix(std::initializer_list<REAL> values)
    {
        Ensure(values.size() == elements_, "Error: Length of initializer list does not match matrix dimensions!");
            
        if constexpr (LAYOUT == MatrixLayout::RowMajor)
        {
            std::copy(values.begin(), values.end(), data_.begin());
        }
        else if constexpr (LAYOUT == MatrixLayout::ColumnMajor)
        {
            auto it = values.begin();
            for (size_t row = 0; row < rows_; ++row)
            for (size_t col = 0; col < cols_; ++col)
            {
                (*this)(row, col) = *it++;
            }
        }
    }

    template <typename REAL, MatrixLayout LAYOUT>
    REAL&  Matrix<REAL, LAYOUT>::operator()(size_t row, size_t col)
    {
        // this if expression should have zero run time overhead
        if constexpr (LAYOUT == MatrixLayout::ColumnMajor)
        {
            // for column major the "fastest changing index" is the row index
            return data_[col * rows_ + row];
        }
        else if constexpr (LAYOUT == MatrixLayout::RowMajor)
        {
            // for row major the "fastest changing index" is the column index
            return data_[row * cols_ + col];
        }
    }

    template <typename REAL, MatrixLayout LAYOUT>
    const REAL&  Matrix<REAL, LAYOUT>::operator()(size_t row, size_t col) const
    {
        // this if expression should have zero run time overhead
        if constexpr (LAYOUT == MatrixLayout::ColumnMajor)
        {
            // for column major the "fastest changing index" is the row index
            return data_[col * rows_ + row];
        }
        else if constexpr (LAYOUT == MatrixLayout::RowMajor)
        {
            // for row major the "fastest changing index" is the column index
            return data_[row * cols_ + col];
        }
    }

    // Matrix Matrix Multiplication
    template <typename REAL, MatrixLayout LAYOUT>
    Matrix<REAL, LAYOUT> Matrix<REAL, LAYOUT>::operator*(const Matrix<REAL, LAYOUT>& B) const
    {
        Matrix<REAL, LAYOUT> C(rows_, B.cols_);

        for (size_t i = 0; i <   rows_; ++i)
        for (size_t j = 0; j < B.cols_; ++j)
        {
            REAL sum = 0;
            for (size_t k = 0; k < cols_; ++k)
            {
                sum += (*this)(i, k) * B(k, j);
            }
            C(i, j) = sum;
        }

        return C;
    }

    template <typename REAL, MatrixLayout LAYOUT>
    void Matrix<REAL, LAYOUT>::DebugPrint(std::string label)
    {
        std::cout << label << " = \n";
        DebugPrint();
    }

    template <typename REAL, MatrixLayout LAYOUT>
    void Matrix<REAL, LAYOUT>::DebugPrint() const
    {
        for (size_t row = 0; row < rows_; ++row)
        {
            std::cout << std::format("{:>12.4f}", (*this)(row, 0));
            for (size_t col = 1; col < cols_; ++col)
            {
                std::cout << std::format(" {:>12.4f}", (*this)(row, col));
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }
}
