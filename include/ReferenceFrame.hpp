#pragma once

#include <format>

#include "Position.hpp"
#include "Attitude.hpp"
#include "Mat4.hpp"
#include "Vec3.hpp"
#include "Units.hpp"

namespace FlightData
{
    class ReferenceFrame
    {
    public:
        ReferenceFrame();
        ReferenceFrame(const Mat4<double> frame);
        ReferenceFrame(const Position position);
        ~ReferenceFrame() = default;

        auto SetPosition(const Position position) -> void;
        auto SetAttitude(const Attitude attitude) -> void;
        
        auto GetPosition() const -> Position;
        auto GetAttitude(const bool positive_heading = true) const -> Attitude;

        auto PrintPosition() const -> void;
        auto PrintAttitude() const -> void;
        auto PrintPosition(const Position position) const -> void;
        auto PrintAttitude(const Attitude attitude) const -> void;

        auto Translate(const Vec3<double> t) -> void;
        auto RotateX(const double angle) -> void;
        auto RotateY(const double angle) -> void;
        auto RotateZ(const double angle) -> void;

        auto Dot(const Mat4<double> &other) -> void;

        auto Orthonormalize() -> void;
        auto GetOrthogonalError() -> double;
        auto GetLengthError() -> double;

    private:
        auto GetEarth2GeodeticMatrix(const Position position) const -> Mat4<double>;
        auto GetGeodetic2EarthMatrix(const Position position) const -> Mat4<double>;
        auto GetGeodetic2BodyfixedMatrix(const Position position) const -> Mat4<double>;

    private:
        static constexpr double earth_radius_ = 6'366'707.0_m;
        Mat4<double> frame_;

        Mat4<double> rotation_matrix_;
        Mat4<double> translation_matrix_;
    };
}

