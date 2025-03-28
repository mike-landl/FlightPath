#pragma once

#include "Units.hpp"

namespace FlightData
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
 * @brief Formatter specialization for FlightData::Position.
 *
 * This specialization allows FlightData::Position to be used with std::format.
 * It converts the longitude and latitude values from radians to degrees, and formats
 * the position in a human-readable string that includes:
 * - Longitude in degrees (6 decimal places)
 * - Latitude  in degrees (6 decimal places)
 * - Altitude  in meters  (2 decimal places)
 */
template <>
struct std::formatter<FlightData::Position>
{

    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::begin(ctx);
    }

    auto format(const FlightData::Position &position, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), 
            "Longitude {:.6f} deg Latitude {:.6f} deg Altitude {:.2f} m",
            rad2deg<double>(position.longitude), rad2deg<double>(position.latitude), position.altitude
        );
    }

};