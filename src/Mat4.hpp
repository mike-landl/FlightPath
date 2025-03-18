#include <array>
#include <print>
#include <iostream>
#include <iomanip>

namespace FlightData
{
    template <typename REAL>
    class Mat4
    {
    public:
        Mat4() = default;

        Mat4(std::initializer_list<REAL> values)
        { 
            if (values.size() != elements_)
            {
                std::println("Error: Length of initializer list does not match matrix dimensions!");
                exit(0);
            }

            std::copy(values.begin(), values.end(), data_.begin());
        };

        ~Mat4() = default;

        void SetMatrix(std::initializer_list<REAL> values)
        {
            std::copy(values.begin(), values.end(), data_.begin());
        }

              REAL& operator()(size_t row, size_t col)       { return data_[row * cols_ + col]; }
        const REAL& operator()(size_t row, size_t col) const { return data_[row * cols_ + col]; }

        // Matrix Matrix Multiplication
        Mat4<REAL> operator*(const Mat4<REAL>& B) const
        {
            Mat4<REAL> C;

            for (size_t i = 0; i < 4; ++i)
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

        void DebugPrint(std::string label)
        {
            std::println(label);
            DebugPrint();
        };

        void DebugPrint() const
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
        }

        // getters for private members
              REAL* RawPtr()       { return data_.data(); }
        const REAL* RawPtr() const { return data_.data(); }

        size_t rows()     const { return rows_; }
        size_t cols()     const { return cols_; }
        size_t elements() const { return elements_; }

    private:
        std::array<REAL, 16> data_;
        static constexpr size_t rows_ = 4;
        static constexpr size_t cols_ = 4;
        static constexpr size_t elements_ = 16;
    };
}