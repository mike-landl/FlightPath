#pragma once

#include <string>
#include <vector>

#include "ReferenceFrame.hpp"

namespace FlightData
{
    /// @brief One line (or entry) in a FlightData Recorder file
    struct Entry
    {
        double time;         ///< time since start of the simulator format:  7.2f unit: s
        double longitude;    ///< longitude                         format: 14.9f unit: deg
        double latitude;     ///< latitude                          format: 13.9f unit: deg
        double altitude;     ///< altitude above sea level          format:  7.1f unit: m
        double true_heading; ///< heading (true north)              format:  5.1f unit: deg
        double pitch;        ///< pitch angle                       format:  5.1f, unit: deg
        double roll;         ///< roll angle                        format:  6.1f, unit: deg
        double v_x;          ///< linear velocity                   format:  6.1f, unit: m/s, type: Body fixed
        double v_y;          ///< linear velocity                   format:  6.1f, unit: m/s, type: Body fixed
        double v_z;          ///< linear velocity                   format:  6.1f, unit: m/s, type: Body fixed
        double omega_x;      ///< rotational velocity               format:  9.3f, unit: deg/s, type: Body fixed
        double omega_y;      ///< rotational velocity               format:  9.3f, unit: deg/s, type: Body fixed
        double omega_z;      ///< rotational velocity               format:  9.3f, unit: deg/s, type: Body fixed
        double a_x;          ///< linear acceleration               format:  9.5f, unit: m/s2,  type: Body fixed
        double a_y;          ///< linear acceleration               format:  9.5f, unit: m/s2,  type: Body fixed
        double a_z;          ///< linear acceleration               format:  9.5f, unit: m/s2,  type: Body fixed
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
