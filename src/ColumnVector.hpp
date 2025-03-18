#pragma once

#include <vector>
#include <initializer_list>

namespace FlightData
{
    template<typename REAL>
    class ColumnVector
    {
    public:
    /* Constructors */
        ColumnVector() = delete;
        ColumnVector(size_t cols);
        ColumnVector(std::initializer_list<REAL> init_list);

    /* Destructor */
        ~ColumnVector() = default;

    /* Operator Overloading */
        auto operator () (size_t col)       ->       REAL& { return m_data[col]; } ;
        auto operator () (size_t col) const -> const REAL& { return m_data[col]; } ;

        ColumnVector<REAL> operator - (const ColumnVector<REAL> B) const
        {
            ColumnVector<REAL> C(m_cols);
            for (size_t col = 0; col < m_cols; ++col)
            {
                C = m_data[col] - B(col);
            }
        }

    /* Getter */
        auto Cols() const -> size_t { return m_cols; };

    private:
        size_t m_cols = 0;
        std::vector<REAL> m_data;
    };

    template<typename REAL>
    ColumnVector<REAL>::ColumnVector(size_t cols)
        : m_cols(cols)
        , m_data(cols, REAL(0.0))
    { 
        // Nothing todo.
    };

    template<typename REAL>
    ColumnVector<REAL>::ColumnVector(std::initializer_list<REAL> init_list)
    {
        m_cols = init_list.size();
        m_data = init_list;
    }
}