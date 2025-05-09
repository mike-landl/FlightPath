#include "ReferenceFrame.hpp"

#include <cmath>

#include "Vec3.hpp"
#include "Units.hpp"
#include "Log.hpp"
#include "Types.hpp"

namespace
{
    static const FlightPath::Mat4<double> IDENTITY_MAT4{
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
}

namespace FlightPath
{
    ReferenceFrame::ReferenceFrame() 
        : frame_{IDENTITY_MAT4}
        , rotation_matrix_{IDENTITY_MAT4}
        , translation_matrix_{IDENTITY_MAT4}
    {
        SetPosition(Position{.longitude=0.0_deg, .latitude=0.0_deg, .altitude=300.0_m});
    }

    ReferenceFrame::ReferenceFrame(const Mat4<double> frame)
        : frame_{frame}
        , rotation_matrix_{IDENTITY_MAT4}
        , translation_matrix_{IDENTITY_MAT4}
    {
    
    }

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

        const double L = position.longitude;
        const double B = position.latitude;
        const double r = earth_radius_ + position.altitude;

        frame_.SetMatrix( 
        { -cos(L)*sin(B), -sin(L), -cos(L)*cos(B), r*cos(L)*cos(B),
          -sin(L)*sin(B),  cos(L), -sin(L)*cos(B), r*sin(L)*cos(B),
                  cos(B),     0.0,        -sin(B),        r*sin(B),
                    0.0,      0.0,            0.0,            1.0
        });
    }

    auto ReferenceFrame::SetAttitude(const Attitude attitude) -> void
    {
        RotateZ(attitude.heading);
        RotateY(attitude.pitch);
        RotateX(attitude.roll);
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

    auto ReferenceFrame::Dot(const Mat4<double> &other) -> void
    {
        frame_ = frame_ * other;
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

        const double L = position.longitude;
        const double B = position.latitude;
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

        const double L = position.longitude;
        const double B = position.latitude;
        const double r = earth_radius_ + position.altitude;

        return Mat4<double>({
            -cos(L)*sin(B), -sin(L)*sin(B),  cos(B), r*cos(L)*cos(B),
            -sin(L)       ,  cos(L)       ,     0.0, r*sin(L)*cos(B),
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

    auto ReferenceFrame::GetAttitude(const bool positive_heading) const -> Attitude
    {
        const auto position = GetPosition();
        const auto iG2B = GetGeodetic2BodyfixedMatrix(position);

        // extract needed matrix entries
        const double i_11 = iG2B(0, 0);
        const double i_21 = iG2B(1, 0);
        const double i_31 = iG2B(2, 0);
        const double i_32 = iG2B(2, 1);
        const double i_33 = iG2B(2, 2);

        const double heading = positive_heading ? std::fmod(TWO_PI_d + std::atan2(i_21, i_11), TWO_PI_d) : std::atan2(i_21, i_11);
        const double pitch   = std::asin(-i_31);
        const double roll    = std::atan2(i_32, i_33);

        return Attitude{.heading=heading, .pitch=pitch, .roll=roll};
    }

    auto ReferenceFrame::PrintPosition() const -> void
    {
        PrintPosition(GetPosition());
    }
    
    auto ReferenceFrame::PrintAttitude() const -> void
    {
        PrintAttitude(GetAttitude());
    }
    
    auto ReferenceFrame::PrintPosition(const Position position) const -> void
    {
        Log::Info(std::format("{}", position));
    }

    auto ReferenceFrame::PrintAttitude(const Attitude attitude) const -> void
    {
        Log::Info(std::format("{}", attitude));
    }

    auto ReferenceFrame::Orthonormalize() -> void
    {
        constexpr double max_error = 1e-15;
        constexpr double max_error_sq = max_error * max_error;
        constexpr i32 max_iter = 10;
        constexpr bool use_fast_approximation = true;

        constexpr double ONE_THIRD = 1.0 / 3.0;
        // Get vectors from rotation part of frame
        Vec3<double> c_i = frame_.GetColumn(0);
        Vec3<double> c_j = frame_.GetColumn(1);
        Vec3<double> c_k = frame_.GetColumn(2);

        // calculate initial deviation from orthogonality
        double d_ij = c_i.Dot(c_j);
        double d_jk = c_j.Dot(c_k);
        double d_ki = c_k.Dot(c_i);

        double error_sq = ONE_THIRD * (d_ij*d_ij + d_jk*d_jk + d_ki*d_ki);

        for (i32 iter = 0; iter < max_iter; ++iter)
        {
            if (error_sq < max_error_sq) break;

            // ortho correction of i,j pair
            d_ij = c_i.Dot(c_j);
            Vec3<double> c_i_hat = c_i - 0.5 * d_ij * c_j;
            Vec3<double> c_j_hat = c_j - 0.5 * d_ij * c_i;

            // ortho correction of j,k pair
            d_jk = c_j_hat.Dot(c_k);
            Vec3<double> c_j_hh  = c_j_hat - 0.5 * d_jk * c_k;
            Vec3<double> c_k_hat = c_k     - 0.5 * d_jk * c_j_hat;

            // ortho correction of k,i pair
            d_ki = c_k_hat.Dot(c_i_hat);
            Vec3<double> c_k_hh = c_k_hat - 0.5 * d_ki * c_i_hat;
            Vec3<double> c_i_hh = c_i_hat - 0.5 * d_ki * c_k_hat;

            // recalculate orthogonal error
            d_ij = c_i_hh.Dot(c_j_hh);
            d_jk = c_j_hh.Dot(c_k_hh);
            d_ki = c_k_hh.Dot(c_i_hh);
            error_sq = ONE_THIRD * (d_ij*d_ij + d_jk*d_jk + d_ki*d_ki);

            // Norm correction (fast approximation) todo: is this needed at every iteration?
            if constexpr (use_fast_approximation)
            {
                double d_ii = 1.0 - c_i_hh.Dot(c_i_hh);
                double d_jj = 1.0 - c_j_hh.Dot(c_j_hh);
                double d_kk = 1.0 - c_k_hh.Dot(c_k_hh);

                c_i = c_i_hh * (1.0 + 0.5 * d_ii);
                c_j = c_j_hh * (1.0 + 0.5 * d_jj);
                c_k = c_k_hh * (1.0 + 0.5 * d_kk);
            }
            else
            {
                c_i = c_i_hh.Normalized();
                c_j = c_j_hh.Normalized();
                c_k = c_k_hh.Normalized();
            }
        }

        // Write back to frame
        frame_.SetColumn(0, c_i);
        frame_.SetColumn(1, c_j);
        frame_.SetColumn(2, c_k);
    }

    auto ReferenceFrame::GetOrthogonalError() -> double
    {
        constexpr double ONE_THIRD = 1.0/3.0;
        // Get vectors from rotation part of frame
        Vec3<double> c_i = frame_.GetColumn(0);
        Vec3<double> c_j = frame_.GetColumn(1);
        Vec3<double> c_k = frame_.GetColumn(2);

        // calculate initial deviation from orthogonality
        double d_ij = c_i.Dot(c_j);
        double d_jk = c_j.Dot(c_k);
        double d_ki = c_k.Dot(c_i);

        return std::sqrt(ONE_THIRD * (d_ij*d_ij + d_jk*d_jk + d_ki*d_ki));
    }

    auto ReferenceFrame::GetLengthError() -> double
    {
        constexpr double ONE_THIRD = 1.0/3.0;
        // Get vectors from rotation part of frame
        Vec3<double> c_i = frame_.GetColumn(0);
        Vec3<double> c_j = frame_.GetColumn(1);
        Vec3<double> c_k = frame_.GetColumn(2);

        double d_ii_sq = std::abs(1.0 - c_i.LengthSquared());
        double d_jj_sq = std::abs(1.0 - c_j.LengthSquared());
        double d_kk_sq = std::abs(1.0 - c_k.LengthSquared());

        return std::sqrt(ONE_THIRD * (d_ii_sq + d_jj_sq + d_kk_sq)); // root-mean-square
    }
}
