#pragma once

/* Templated PI */

/**
 * @brief Returns the mathematical constant PI as a constexpr of the specified real type.
 *
 * @tparam REAL           The floating-point type to return (e.g., float, double, long double).
 * @return constexpr REAL The value of PI as the specified type.
 */
template <typename REAL>
constexpr REAL PI()
{
    return static_cast<REAL>(3.14159265358979323846264338327950288419716939937510l);
}

/**
 * @brief Returns the mathematical constant two times PI as a constexpr of the specified real type.
 *
 * @tparam REAL           The floating-point type to return (e.g., float, double, long double).
 * @return constexpr REAL The value of two times PI as the specified type.
 */
template <typename REAL>
constexpr REAL TWO_PI()
{
    return static_cast<REAL>(2.0l * PI<long double>());
}

// convenience definitions
constexpr float  PI_f = PI<float>();
constexpr double PI_d = PI<double>();
constexpr float  TWO_PI_f = TWO_PI<float>();
constexpr double TWO_PI_d = TWO_PI<double>();


/* Unit conversion functions */

/**
 * @brief Converts an angle from degrees to radians.
 *
 * @tparam T     The numeric type (i.e. float or double) to cast the converted value to.
 * @param  value The angle in degrees.
 * @return       The angle in radians, cast to the specified type \p T.
 */
template <typename T>
constexpr T deg2rad(const long double value)
{
    constexpr long double factor = PI<long double>() / 180.0l;
    return static_cast<T>(value * factor);
}

/**
 * @brief Converts an angle from radians to degrees.
 *
 * @tparam T     The numeric type (i.e. float or double) to cast the converted value to.
 * @param  value The angle in radians.
 * @return       The angle in degrees, cast to the specified type \p T.
 */
template <typename T>
constexpr T rad2deg(const long double value)
{
    constexpr long double factor = 180.0l / PI<long double>();
    return static_cast<T>(value * factor);
}

/**
 * @brief Converts a length from millimeters to meters
 *
 * @tparam T     The numeric type (i.e. float or double) to cast the converted value to.
 * @param  value The length in millimeters.
 * @return       The length in meters, cast to the specified type \p T.
 */
template <typename T>
constexpr T mm2m(const long double value)
{
    constexpr long double factor = 1.0l / 1000.0l;
    return static_cast<T>(value * factor);
}

/**
 * @brief Passthrough for meters - kept for consitency in the codebase
 *
 * @tparam T     The numeric type (i.e. float or double) to cast the converted value to.
 * @param  value The length in meters.
 * @return       The length in meters, cast to the specified type \p T.
 */
template <typename T>
constexpr T m2m(const long double value)
{
    constexpr long double factor = 1.0l;
    return static_cast<T>(value * factor);
}

/**
 * @brief Converts a length from kilometers to meters
 *
 * @tparam T     The numeric type (i.e. float or double) to cast the converted value to.
 * @param  value The length in kilometers.
 * @return       The length in meters, cast to the specified type \p T.
 */
template <typename T>
constexpr T km2m(const long double value)
{
    constexpr long double factor = 1000.0l;
    return static_cast<T>(value * factor);
}

/**
 * @brief Converts a length from meters to feet
 *
 * @tparam T     The numeric type (i.e. float or double) to cast the converted value to.
 * @param  meter The length in meters.
 * @return       The length in feet, cast to the specified type \p T.
 */
template <typename T>
constexpr T m2ft(const long double meter)
{
    constexpr long double factor = 1.0l / 0.3048l;
    return static_cast<T>(meter * factor);
}

/**
 * @brief Converts a length from feet to meters
 *
 * @tparam T    The numeric type (i.e. float or double) to cast the converted value to.
 * @param  feet The length in feet.
 * @return      The length in meeters, cast to the specified type \p T.
 */
template <typename T>
constexpr T ft2m(const long double feet)
{
    constexpr long double factor = 0.3048l;
    return static_cast<T>(feet * factor);
}


/* Custom double literals for unit conversion */

/// @brief Custom literal for degrees to radians conversion
constexpr double operator"" _deg(long double value) { return deg2rad<double>(value); }

/// @brief Custom literal for milimeter to meter conversion
constexpr double operator"" _mm (long double value) { return    mm2m<double>(value); }

/// @brief Custom literal for meter passthrough
constexpr double operator"" _m  (long double value) { return     m2m<double>(value); }

/// @brief Custom literal for degrees to radians conversion
constexpr double operator"" _km (long double value) { return    km2m<double>(value); }

/// @brief Custom literal for feet to meter conversion
constexpr double operator"" _ft (long double value) { return    ft2m<double>(value); }


/* Custom float literals for unit conversion */

/// @brief Custom literal for degrees to radians conversion
constexpr float operator"" _deg_f(long double value) { return deg2rad<float>(value); }
                                                              
/// @brief Custom literal for milimeter to meter conversion
constexpr float operator"" _mm_f (long double value) { return    mm2m<float>(value); }
                                                              
/// @brief Custom literal meter passthrough                   
constexpr float operator"" _m_f  (long double value) { return     m2m<float>(value); }
                                                              
/// @brief Custom literal for degrees to radians conversion
constexpr float operator"" _km_f (long double value) { return    km2m<float>(value); }
                                                              
/// @brief Custom literal for feet to meter conversion        
constexpr float operator"" _ft_f (long double value) { return    ft2m<float>(value); }
