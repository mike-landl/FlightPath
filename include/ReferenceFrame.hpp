#pragma once

#include <format>

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

template <>
struct std::formatter<FlightData::Position>
{

    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::begin(ctx);
    }

    auto format(const FlightData::Position &position, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), 
            "Longitude {:.6f} deg Latitude {:.6f} deg Altitude {:.2f} m",
            rad2deg<double>(position.longitude), rad2deg<double>(position.latitude), position.altitude
        );
    }

};

template <>
struct std::formatter<FlightData::Attitude>
{

    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::begin(ctx);
    }

    auto format(const FlightData::Attitude &attitude, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), 
            "Heading {:.2f} deg, Pitch {:.2f} deg, Roll {:.2f} deg",
            rad2deg<double>(attitude.heading), rad2deg<double>(attitude.pitch), rad2deg<double>(attitude.roll)
        );
    }

};
