#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <initializer_list>

#include "ColumnVector.hpp"

namespace FlightData
{
    enum class MatrixLayout
    {
        RowMajor,
        ColumnMajor
    };

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
        void SetMatrix(std::initializer_list<REAL> values)
        {
            if (values.size() != elements_)
            {
                std::cout << "Error: Length of initializer list does not match matrix dimensions!";
                exit(0);
            }

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

        REAL& operator()(size_t row, size_t col)
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

        const REAL& operator()(size_t row, size_t col) const
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
        Matrix<REAL, LAYOUT> operator*(const Matrix<REAL, LAYOUT>& B) const
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

        void DebugPrint(std::string label);
        void DebugPrint() const;

        // getters for private members
              REAL* RawPtr()       { return data_.data(); }
        const REAL* RawPtr() const { return data_.data(); }

        size_t rows()     const { return rows_; }
        size_t cols()     const { return cols_; }
        size_t elements() const { return elements_; }

    private:
        std::vector<REAL> data_;
        size_t rows_ = 0;
        size_t cols_ = 0;
        size_t elements_ = 0;
    };


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
            for (size_t col = 0; col < cols_; ++col)
            {
                std::cout << std::setw(12) << std::right << std::setprecision(4) << std::fixed
                          << (*this)(row, col) << " ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }
}