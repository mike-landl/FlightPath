#pragma once

#include "Mat4.hpp"
#include "Vec3.hpp"
#include "ReferenceFrame.hpp"
#include "Recorder.hpp"

/**
 * @namespace FlightPath
 * @brief Main namespace for this project
 */
namespace FlightPath
{
    /**
     * @class Application
     * @brief Main application class responsible for reconstruction of the flight path based on body fixed accelerations and velocities.
     */
    class Application
    {
    public:
        /// @brief Default constructor. Reads a default flight data file and initialized the reference frame and body frame velocity vectors
        Application();
        
        /// @brief Default destructor.
        ~Application() = default;

        /// @brief Runs the main function for reconstructing the flight path
        auto Run() -> void;

    private:

    private:

        ReferenceFrame reference_frame_; ///< Reference frame used for flight data calculations.
        Recorder recorder_;              ///< Recorder used to read and store flight data.
        
        Vec3<double> vb_n_{0,0,0};       ///< Body-frame velocity vector at time step n   in the navigation frame.
        Vec3<double> vb_np1_{0,0,0};     ///< Body-frame velocity vector at time step n+1 in the navigation frame.
    };

}
