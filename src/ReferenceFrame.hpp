#pragma once

#include "Mat4.hpp"
#include "Vec3.hpp"
#include "Units.hpp"

namespace FlightData
{

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

        auto PrintPosition() const -> void;
        auto PrintAttitude() const -> void;
        auto PrintPosition(const Position position) const -> void;
        auto PrintAttitude(const Attitude attitude) const -> void;

        auto Translate(const Vec3<double> t) -> void;
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
