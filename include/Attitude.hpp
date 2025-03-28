#pragma once

namespace FlightData
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
 * @brief Formatter specialization for FlightData::Attitude.
 *
 * This specialization enables the use of std::format with FlightData::Attitude.
 * It converts heading, pitch, and roll values from radians to degrees, and formats
 * the attitude as a readable string with each angle shown to two decimal places.
 */
template <>
struct std::formatter<FlightData::Attitude>
{

    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::begin(ctx);
    }

    auto format(const FlightData::Attitude &attitude, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), 
            "Heading {:.2f} deg, Pitch {:.2f} deg, Roll {:.2f} deg",
            rad2deg<double>(attitude.heading), rad2deg<double>(attitude.pitch), rad2deg<double>(attitude.roll)
        );
    }

};