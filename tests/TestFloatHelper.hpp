#include <limits>    

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

/**
 * @brief Checks whether two floating-point values are approximately equal.
 * 
 * This function uses Catch2's WithinRel matcher to assert that the actual value
 * is within a specified number of ULPs (units in the last place) relative to the expected value.
 *
 * @tparam REAL     A floating-point type (e.g., float, double).
 * @param  value    The actual value to check.
 * @param  expected The expected value to compare against.
 * @param  ulps     The number of ULPs (in terms of machine epsilon) allowed as relative tolerance.
 * 
 * @note This function is intended for use in unit tests to validate floating-point results 
 *       with a controlled tolerance.
 */
template <typename REAL>
inline auto CheckReal(const REAL value, const REAL expected, const REAL ulps = REAL(1)) -> void
{
    REQUIRE_THAT(
        value,
        Catch::Matchers::WithinRel(
            expected,
            ulps*std::numeric_limits<REAL>::epsilon()
        )
    );
}