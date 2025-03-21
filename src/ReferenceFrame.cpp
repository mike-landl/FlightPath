#include "ReferenceFrame.hpp"
#include <cmath>
#include "Vec3.hpp"

namespace
{
    static const FlightData::Mat4<double> IDENTITY_MAT4{
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
}

namespace FlightData
{
    ReferenceFrame::ReferenceFrame() 
        : frame_{IDENTITY_MAT4}
        , rotation_matrix_{IDENTITY_MAT4}
        , translation_matrix_{IDENTITY_MAT4}
    {
    
    };

    ReferenceFrame::ReferenceFrame(const Position position)
        : frame_{IDENTITY_MAT4}
        , rotation_matrix_{IDENTITY_MAT4}
        , translation_matrix_{IDENTITY_MAT4}
    {
        SetPosition(position);
    }

    auto ReferenceFrame::SetPosition(const Position position) -> void
    {
        using std::sin;
        using std::cos;

        const double r = earth_radius_ + position.altitude;
        const double L = position.longitude;
        const double B = position.latitude;

        frame_.SetMatrix( 
        { -cos(L)*sin(B), -sin(L), -cos(L)*cos(B), r*cos(L)*cos(B),
          -sin(L)*sin(B),  cos(L), -sin(L)*cos(B), r*sin(L)*cos(B),
                  cos(B),     0.0,        -sin(B),        r*sin(B),
                    0.0,      0.0,            0.0,            1.0
        });
    }

    auto ReferenceFrame::Translate(const Vec3<double> t) -> void
    {
        translation_matrix_.SetMatrix({
            1.0, 0.0, 0.0, t.x,
            0.0, 1.0, 0.0, t.y,
            0.0, 0.0, 1.0, t.z,
            0.0, 0.0, 0.0, 1.0 
        });
        frame_ = frame_ * translation_matrix_;
    }

    auto ReferenceFrame::RotateX(const double angle) -> void
    {
        const double sin_a = std::sin(angle);
        const double cos_a = std::cos(angle);
        rotation_matrix_.SetMatrix({
            1.0,   0.0,    0.0, 0.0,
            0.0, cos_a, -sin_a, 0.0,
            0.0, sin_a,  cos_a, 0.0,
            0.0,   0.0,    0.0, 1.0
        });
        frame_ = frame_ * rotation_matrix_;
    }

    auto ReferenceFrame::RotateY(const double angle) -> void
    {
        const double sin_a = std::sin(angle);
        const double cos_a = std::cos(angle);
        rotation_matrix_.SetMatrix({
             cos_a, 0.0, sin_a, 0.0,
               0.0, 1.0,   0.0, 0.0,
            -sin_a, 0.0, cos_a, 0.0,
               0.0, 0.0,   0.0, 1.0
        });
        frame_ = frame_ * rotation_matrix_;
    }

    auto ReferenceFrame::RotateZ(const double angle) -> void
    {
        const double sin_a = std::sin(angle);
        const double cos_a = std::cos(angle);
        rotation_matrix_.SetMatrix({
            cos_a, -sin_a, 0.0, 0.0,
            sin_a,  cos_a, 0.0, 0.0,
              0.0,    0.0, 1.0, 0.0,
              0.0,    0.0, 0.0, 1.0
        });
        frame_ = frame_ * rotation_matrix_;
    }

    auto ReferenceFrame::GetPosition() const -> Position
    {
        const double i_14 = frame_(0, 3);
        const double i_24 = frame_(1, 3);
        const double i_34 = frame_(2, 3);

        const double r = std::sqrt(i_14*i_14 + i_24*i_24 + i_34*i_34);

        const double longitude = std::atan2(i_24, i_14);
        const double latitude  = std::asin(i_34 / r);
        const double altitude  = r - earth_radius_;
        
        return Position{
            .longitude = longitude,
            .latitude  =  latitude,
            .altitude  =  altitude
        };
    }

    auto ReferenceFrame::GetEarth2GeodeticMatrix(const Position position) const -> Mat4<double>
    {
        using std::sin;
        using std::cos;

        const double L = position.latitude;
        const double B = position.altitude;
        const double r = earth_radius_ + position.altitude;

        return Mat4<double>({
           -cos(L)*sin(B), -sin(L), -cos(L)*cos(B), r*cos(L)*cos(B),
           -sin(L)*sin(B),  cos(L), -sin(L)*cos(B), r*sin(L)*cos(B),
                   cos(B),     0.0,        -sin(B),        r*sin(B),
                      0.0,     0.0,            0.0,             1.0
        });
    }

    auto ReferenceFrame::GetGeodetic2EarthMatrix(const Position position) const -> Mat4<double>
    {
        using std::sin;
        using std::cos;

        const double L = position.latitude;
        const double B = position.altitude;
        const double r = earth_radius_ + position.altitude;

        return Mat4<double>({
            -cos(L)*sin(B), -sin(L)*sin(B),  cos(B), r*cos(L)*cos(B),
                   -sin(L),         cos(L),     0.0, r*sin(L)*cos(B),
            -cos(L)*cos(B), -sin(L)*cos(B), -sin(B),        r*sin(B),
                       0.0,            0.0,     0.0,             1.0
        });
    }

    auto ReferenceFrame::GetGeodetic2BodyfixedMatrix(const Position position) const -> Mat4<double>
    {
        const auto  iG2E = GetGeodetic2EarthMatrix(position);
        const auto &iE2B = frame_; // transformation matrix from earth to bodyfixed (i.e. our reference frame)
        const auto  iG2B = iG2E * iE2B;
        return iG2B;
    }

    auto ReferenceFrame::GetAttitude() const -> Attitude
    {
        const auto position = GetPosition();
        const auto iG2B = GetGeodetic2BodyfixedMatrix(position);

        // extract needed matrix entries
        const double i_11 = iG2B(0, 0);
        const double i_21 = iG2B(1, 0);
        const double i_31 = iG2B(2, 0);
        const double i_32 = iG2B(2, 1);
        const double i_33 = iG2B(2, 2);

        const double heading = std::atan2(i_21, i_11);
        const double pitch   = std::asin(-i_31);
        const double roll    = std::atan2(i_32, i_33);

        return Attitude{.heading=heading, .pitch=pitch, .roll=roll};
    }
}