#pragma once

#include "Units.hpp"

namespace FlightPath
{
    /**
     * @struct Position
     * @brief Geographic position of an object
     * 
     * Represents a geographic position with longitude, latitude, and altitude.
     */
    struct Position
    {
        double longitude; ///< longitude in radians
        double latitude;  ///< latitude  in radians
        double altitude;  ///< altitude  in meters
    };
}

/**
 * @brief Formatter specialization for FlightPath::Position.
 *
 * This specialization allows FlightPath::Position to be used with std::format.
 * It converts the longitude and latitude values from radians to degrees, and formats
 * the position in a human-readable string that includes:
 * - Longitude in degrees (6 decimal places)
 * - Latitude  in degrees (6 decimal places)
 * - Altitude  in meters  (2 decimal places)
 */
template <>
struct std::formatter<FlightPath::Position>
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
     * @brief  Formats the FlightPath::Position object.
     * 
     * @param  position The FlightPath::Position instance to format.
     * @param  ctx      The format context to write to.
     * @return          An iterator to the end of the output.
     */
    auto format(const FlightPath::Position &position, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), 
            "Longitude {:.6f} deg Latitude {:.6f} deg Altitude {:.2f} m",
            rad2deg<double>(position.longitude), rad2deg<double>(position.latitude), position.altitude
        );
    }

};