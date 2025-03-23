#include "Solver.hpp"
#include "Log.hpp"

namespace FlightData
{
    Solver::Solver()
    {
        recorder_.ReadFile("../../../data/2017-01-17_Graz-Gleichenberg.txt");
        const auto& data = recorder_.GetData();
        Log::Info("Successfully read flight data file with {} entries.", data.size());
        
        const auto &entry = data[0];
        reference_frame_.SetPosition(
            Position{
                .longitude = entry.longitude,
                .latitude  = entry.latitude,
                .altitude  = entry.altitude}
        );

        reference_frame_.SetAttitude(
            Attitude{
                .heading = entry.true_heading, 
                .pitch   = entry.pitch,    
                .roll    = entry.roll}
        );
        Log::Info("Initialized reference frame to");
        reference_frame_.PrintPosition();
        reference_frame_.PrintAttitude();
    }

    auto Solver::Run() -> void
    {
        const auto& data = recorder_.GetData();
        const Mat4<double> eye_4{
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        for (size_t idx = 1; idx < data.size(); ++idx)
        {
            if (idx % 100 == 0) Log::Info("{}", (double)idx);

            // calculate acceleration
            Vec3<double> vb = Vec3<double>(data[idx-1].v_x,     data[idx-1].v_y,     data[idx-1].v_z);
            Vec3<double> ab = Vec3<double>(data[idx-1].a_x,     data[idx-1].a_y,     data[idx-1].a_z);
            Vec3<double> ob = Vec3<double>(data[idx-1].omega_x, data[idx-1].omega_y, data[idx-1].omega_z);
            double dt = data[idx].time - data[idx-1].time;

            Vec3<double> dv_dt_b = ab - ob.Cross(vb);

            Mat4<double> twist_matrix = {
                  0.0, -ob.z,  ob.y, vb.x,
                 ob.z,   0.0, -ob.x, vb.y,
                -ob.y,  ob.x,   0.0, vb.z,
                  0.0,   0.0,   0.0,  0.0
            };

            // integrate
            vb = vb + dv_dt_b * dt;
            reference_frame_.Dot(eye_4 + twist_matrix * dt);

            // correct the transform
            
            // store flight data
        }
    }
}
