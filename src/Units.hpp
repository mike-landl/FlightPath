#pragma once

static constexpr long double PI = 3.14159265358979323846264338327950288419716939937510l;

constexpr double deg2rad(long double value)
{
    constexpr long double factor = PI / 180.0l;
    return static_cast<double>(value * factor);
}

constexpr double rad2deg(long double value)
{
    constexpr long double factor = 180.0l / PI;
    return static_cast<double>(value * factor);
}

constexpr double mm2m(long double value)
{
    constexpr long double factor = 1.0l / 1000.0l;
    return static_cast<double>(value * factor);
}

constexpr double km2m(long double value)
{
    constexpr long double factor = 1000.0l;
    return static_cast<double>(value * factor);
}

constexpr double m2ft(long double feet)
{
    constexpr long double factor = 1.0l / 0.3048l;
    return static_cast<double>(feet * factor);
}

constexpr double ft2m(long double meter)
{
    constexpr long double factor = 0.3048l;
    return static_cast<double>(meter * factor);
}

constexpr double operator"" _deg(long double value)
{
    return deg2rad(value);
}

constexpr double operator"" _mm(long double value)
{
    return static_cast<double>(mm2m(value));
}

constexpr double operator"" _m(long double value)
{
    return static_cast<double>(value);
}

constexpr double operator"" _km(long double value)
{
    return static_cast<double>(km2m(value));
}

constexpr double operator"" _ft(long double value)
{
    return static_cast<double>(ft2m(value));
}
