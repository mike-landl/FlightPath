#include <format>

#include "Solver.hpp"
#include "Log.hpp"

namespace FlightData
{
    Solver::Solver()
    {
        Log::Info("Reading flight data file...");
        recorder_.ReadFile("./data/2017-01-17_Graz-Gleichenberg.txt");
        const auto& data = recorder_.GetData();
        Log::Info(std::format("Reading flight data file... Done {} entries.", data.size()));
        
        const auto &entry = data[0];
        reference_frame_.SetPosition(
            Position{
                .longitude = entry.longitude,
                .latitude  = entry.latitude,
                .altitude  = entry.altitude}
        );

        Log::Info("Initializing reference frame...");
        reference_frame_.SetAttitude(
            Attitude{
                .heading = entry.true_heading, 
                .pitch   = entry.pitch,    
                .roll    = entry.roll}
        );
        Log::Info("Initializing reference frame... Done");
        reference_frame_.PrintPosition();
        reference_frame_.PrintAttitude();

        Log::Info("Initializing aircraft velocity... Done");
        vb_np1_ = Vec3(entry.v_x, entry.v_y, entry.v_z);
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
        
        Log::Info("Calculating flight path...");
        for (size_t idx = 0; idx < data.size() - 1; ++idx)
        {
            vb_n_ = vb_np1_;

            // calculate acceleration (ab and ob comes from logfile)
            const Vec3<double> ab = Vec3<double>(data[idx].a_x,     data[idx].a_y,     data[idx].a_z);
            const Vec3<double> ob = Vec3<double>(data[idx].omega_x, data[idx].omega_y, data[idx].omega_z);
            const double dt = data[idx+1].time - data[idx].time;

            const Vec3<double> dv_dt_b = ab - ob.Cross(vb_n_);

            const Mat4<double> twist_matrix = {
                  0.0, -ob.z,  ob.y, vb_n_.x,
                 ob.z,   0.0, -ob.x, vb_n_.y,
                -ob.y,  ob.x,   0.0, vb_n_.z,
                  0.0,   0.0,   0.0,     0.0
            };

            // integration yields velocity and new position + attitude
            vb_np1_ = vb_n_ + dv_dt_b * dt;
            reference_frame_.Dot(eye_4 + twist_matrix * dt);

            // correct the transform
            reference_frame_.Orthonormalize();

            // store flight data in recorder
            recorder_.WriteData(
                reference_frame_.GetPosition(), 
                reference_frame_.GetAttitude(),
                vb_np1_
            );
        }
        Log::Info("Calculating flight path... Done");
        Log::Info("Final Position:");
        reference_frame_.PrintPosition();
        reference_frame_.PrintAttitude();
        
        Log::Info("Exporting KML file...");
        recorder_.DumpKML("./data/2017-01-17_Graz-Gleichenberg.kml");
        Log::Info("Exporting KML file... Done");
    }
}
