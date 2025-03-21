#pragma once

#include "Vec3.hpp"
#include "Mat4.hpp"

namespace FlightData
{

    class VelocityState
    {
    public:
         VelocityState() = default;
        ~VelocityState() = default;

        auto SetState(const Vec3<double> omega, const Vec3<double> vel) -> void;

    private:
        Mat4<double> state_;
    };
}