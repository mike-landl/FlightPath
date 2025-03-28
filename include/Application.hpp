#pragma once

#include "Mat4.hpp"
#include "Vec3.hpp"
#include "ReferenceFrame.hpp"
#include "Recorder.hpp"

namespace FlightData
{
    class Application
    {
    public:
        Application();
        ~Application() = default;

        auto Run() -> void;

    private:

    private:

        ReferenceFrame reference_frame_;
        Recorder recorder_;
        
        Vec3<double> vb_n_{0,0,0};
        Vec3<double> vb_np1_{0,0,0};
    };

}
