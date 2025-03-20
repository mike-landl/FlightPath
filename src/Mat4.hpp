#include <array>
#include <iostream>
#include <format>

#include "Error.hpp"

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

        void SetMatrix(std::initializer_list<REAL> values)
        {
            std::copy(values.begin(), values.end(), data_.begin());
        }

        // Operator overloading
              REAL& operator()(size_t row, size_t col)       { return data_[row * cols_ + col]; }
        const REAL& operator()(size_t row, size_t col) const { return data_[row * cols_ + col]; }

        // Matrix Matrix Multiplication
        Mat4<REAL> operator*(const Mat4<REAL>& B) const
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

        void DebugPrint(std::string label);
        void DebugPrint() const;

        // getters for private members
        auto RawPtr()       ->       REAL* { return data_.data(); }
        auto RawPtr() const -> const REAL* { return data_.data(); }

        auto rows()     const -> size_t { return rows_; }
        auto cols()     const -> size_t { return cols_; }
        auto elements() const -> size_t { return elements_; }

    private:
        std::array<REAL, 16> data_;
        static constexpr size_t rows_ = 4;
        static constexpr size_t cols_ = 4;
        static constexpr size_t elements_ = 16;
    };

    template <typename REAL>
    void Mat4<REAL>::DebugPrint(std::string label)
    {
        std::println(label);
        DebugPrint();
    };

    template <typename REAL>
    void Mat4<REAL>::DebugPrint() const
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
