#include "Recorder.hpp"

#include <fstream>
#include <sstream>
#include <ranges>

#include "Error.hpp"
#include "Units.hpp"
#include "KML.hpp"

namespace FlightPath
{
    // overload stream operator for input file stream
    // reads a line and converts units to SI unit
    static std::istream& operator>>(std::istream &input_stream, Entry &entry)
    {
        if (input_stream 
            >> entry.time
            >> entry.longitude
            >> entry.latitude   
            >> entry.altitude 
            >> entry.true_heading
            >> entry.pitch
            >> entry.roll
            >> entry.v_x         
            >> entry.v_y         
            >> entry.v_z      
            >> entry.omega_x   
            >> entry.omega_y   
            >> entry.omega_z
            >> entry.a_x       
            >> entry.a_y       
            >> entry.a_z)
        {
            entry.longitude    = deg2rad<double>(entry.longitude);
            entry.latitude     = deg2rad<double>(entry.latitude);

            entry.true_heading = deg2rad<double>(entry.true_heading);
            entry.pitch        = deg2rad<double>(entry.pitch);
            entry.roll         = deg2rad<double>(entry.roll);

            entry.omega_x      = deg2rad<double>(entry.omega_x);
            entry.omega_y      = deg2rad<double>(entry.omega_y);
            entry.omega_z      = deg2rad<double>(entry.omega_z);
        }
        return input_stream;
    }

    auto Recorder::ReadFile(const std::string &path) -> void
    {
        std::ifstream file(path);
        
        Ensure(file.is_open(), "Recorder: Could not open file {}", path);

        Entry entry{};
        while (file >> entry)
        {
            input_data_.push_back(entry);
        }
        
        // copy first line of input to output
        output_data_.push_back(input_data_[0]);
    }

    auto Recorder::WriteData(const Position &position, const Attitude &attitude, const Vec3<double> &velocity) -> void
    {
        // start with a copy of the input data at n and overwrite fields with our calculation
        Entry entry = input_data_[output_data_.size()];
        
        entry.longitude    = position.longitude;
        entry.latitude     = position.latitude;
        entry.altitude     = position.altitude;
        
        entry.true_heading = attitude.heading;
        entry.pitch        = attitude.pitch;
        entry.roll         = attitude.roll;
        
        entry.v_x          = velocity.x;
        entry.v_y          = velocity.y;
        entry.v_z          = velocity.z;
        
        output_data_.push_back(entry);
    }

    auto Recorder::DumpKML(const std::string &path) const -> void
    {
        std::ofstream file(path);
        
        Ensure(file.is_open(), "Recorder: Could not open file {}", path);

        file << KML::Header;

        file << KML::OpenOriginalDataset;
        for (auto &entry : input_data_ | std::views::stride(100))
        {
            file << "            " 
                 << std::format("{:12.9f}, {:12.9f}, {:6.1f}\n",
                    rad2deg<double>(entry.longitude),
                    rad2deg<double>(entry.latitude),
                    entry.altitude);
        }
        file << KML::CloseDataset;

        file << KML::OpenReconstructedDataset;
        for (auto &entry : output_data_ | std::views::stride(100))
        {
            file << "            " 
                 << std::format("{:12.9f}, {:12.9f}, {:6.1f}\n", 
                    rad2deg<double>(entry.longitude),
                    rad2deg<double>(entry.latitude),
                    entry.altitude);
        }
        file << KML::CloseDataset;

        file << KML::Footer;
    }
}
