#pragma once

#include "Mat4.hpp"
#include "ReferenceFrame.hpp"
#include "Recorder.hpp"

namespace FlightData
{
    class Solver
    {
    public:
        Solver();
        ~Solver() = default;

        auto Run() -> void;

    private:

    private:

        ReferenceFrame reference_frame_;
        Recorder recorder_;
    };

}
