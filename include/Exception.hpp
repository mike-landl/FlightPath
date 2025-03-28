#pragma once

#include <stdexcept>
#include <cstdint>
#include <string>

#include <format>

namespace FlightData
{
    /**
     * @class Exception
     * @brief Custom exception class for flight data-related errors.
     *
     * This class extends std::runtime_error to provide specific error handling
     * within the FlightData namespace.
     */
    class Exception : public std::runtime_error
    {
    public:
        /**
         * @brief Constructs a new FlightData::Exception object.
         * @param what A description of the error.
         */
        Exception(const std::string &what);
    };

}

/**
 * @brief Formatter specialization for FlightData::Exception.
 *
 * Enables the use of std::format with FlightData::Exception, formatting
 * the exception using its what() message.
 */
template <>
struct std::formatter<FlightData::Exception>
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
     * @brief  Formats the FlightData::Exception object.
     * 
     * @param  obj The FlightData::Exception instance to format.
     * @param  ctx The format context to write to.
     * @return     An iterator to the end of the output.
     */
    auto format(const FlightData::Exception &obj, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "{}", obj.what());
    }

};
