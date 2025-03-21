#pragma once

#include "VelocityState.hpp"

namespace FlightData
{



    auto VelocityState::SetState(const Vec3<double> omega, const Vec3<double> vel) -> void
    {
        state_ = {
                 0.0, -omega.z,  omega.y, vel.x,
             omega.z,      0.0, -omega.x, vel.y,
            -omega.y,  omega.x,      0.0, vel.z,
                 0.0,      0.0,      0.0,   0.0
        };
    }
}