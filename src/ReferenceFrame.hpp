#pragma once

#include "Mat4.hpp"

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

constexpr double operator"" _deg(long double value)
{
    return deg2rad(value);
}

constexpr double operator"" _m(long double value)
{
    return static_cast<double>(value);
}

constexpr double operator"" _km(long double value)
{
    return static_cast<double>(value * 1000.0l);
}

namespace FlightData
{
    struct Vector3
    {
        double x, y, z;
        Vector3() : x(0), y(0), z(0) {};
        Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
    };

    struct Position
    {
        double longitude, latitude, altitude;
    };

    struct Attitude
    {
        double heading, pitch, roll;
    };

    class ReferenceFrame
    {
    public:
        ReferenceFrame();
        ReferenceFrame(const Position position);
        ~ReferenceFrame() = default;

        auto SetPosition(const Position position) -> void;
        auto GetAttitude() const -> Attitude;
        auto GetPosition() const -> Position;

        auto Translate(const Vector3 t) -> void;
        auto RotateX(const double angle) -> void;
        auto RotateY(const double angle) -> void;
        auto RotateZ(const double angle) -> void;

    private:
        auto GetEarth2GeodeticMatrix(const Position position) const -> Mat4<double>;
        auto GetGeodetic2EarthMatrix(const Position position) const -> Mat4<double>;
        auto GetGeodetic2BodyfixedMatrix(const Position position) const -> Mat4<double>;

    private:
        static constexpr double earth_radius_ = 6366707.0_m;
        Mat4<double> frame_;

        Mat4<double> rotation_matrix_;
        Mat4<double> translation_matrix_;
    };
}
