#pragma once

#include <string>
#include <vector>

#include "ReferenceFrame.hpp"

namespace FlightData
{
    struct Entry
    {                        // Format  Unit   Reference     Type
        double time;         //  7.2    s                  Measured
        double longitude;    // 14.9    deg                Calculated
        double latitude;     // 13.9    deg                Calculated
        double altitude;     //  7.1    m                  Calculated
        double true_heading; //  5.1    deg                Calculated
        double pitch;        //  5.1    deg                Calculated
        double roll;         //  6.1    deg                Calculated
        double v_x;          //  6.1    m/s    Body fixed  Calculated
        double v_y;          //  6.1    m/s    Body fixed  Calculated
        double v_z;          //  6.1    m/s    Body fixed  Calculated
        double omega_x;      //  9.3    deg/s  Body fixed  Measured
        double omega_y;      //  9.3    deg/s  Body fixed  Measured
        double omega_z;      //  9.3    deg/s  Body fixed  Measured
        double a_x;          //  9.5    m/s2   Body fixed  Measured
        double a_y;          //  9.5    m/s2   Body fixed  Measured
        double a_z;          //  9.5    m/s2   Body fixed  Measured
    };

    class Recorder
    {
    public: 
         Recorder() = default;
        ~Recorder() = default;

        auto ReadFile(const std::string &path) -> void;

        auto GetData() const -> const std::vector<Entry>& { return input_data_; }
        auto WriteData(const Position &position, const Attitude &attitude, const Vec3<double> &velocity) -> void;

        auto DumpKML(const std::string &path) const -> void;

    private:

    private:
        std::vector<Entry>  input_data_;
        std::vector<Entry> output_data_;
    };
}
