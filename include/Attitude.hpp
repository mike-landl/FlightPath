#pragma once

#include <format>

#include "Units.hpp"

namespace FlightPath
{
    /**
     * @struct Attitude
     * @brief Orientation of an object
     * 
     * Represents the orientation of an object in terms of heading, pitch, and roll.
     */
    struct Attitude
    {
        double heading; ///< Heading (yaw) angle in degrees
        double pitch;   ///< pitch angle in degrees
        double roll;    ///< roll angle in degrees
    };
}

/**
 * @brief Formatter specialization for FlightPath::Attitude.
 *
 * This specialization enables the use of std::format with FlightPath::Attitude.
 * It converts heading, pitch, and roll values from radians to degrees, and formats
 * the attitude as a readable string with each angle shown to two decimal places.
 */
template <>
struct std::formatter<FlightPath::Attitude>
{
    /**
     * @brief  Parses the format specifier (unused in this case).
     * 
     * @param  ctx The format parse context.
     * @return     An iterator pointing to the end of the parsed format specifier.
     */
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::begin(ctx);
    }

    /**
     * @brief  Formats the FlightPath::Attidude object.
     * 
     * @param  attitude The FlightPath::Attidude instance to format.
     * @param  ctx      The format context to write to.
     * @return          An iterator to the end of the output.
     */
    auto format(const FlightPath::Attitude &attitude, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), 
            "Heading {:.2f} deg, Pitch {:.2f} deg, Roll {:.2f} deg",
            rad2deg<double>(attitude.heading), rad2deg<double>(attitude.pitch), rad2deg<double>(attitude.roll)
        );
    }

};