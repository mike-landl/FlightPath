#pragma once

#include <stdexcept>
#include <cstdint>
#include <string>

#include <format>

namespace FlightPath
{
    /**
     * @class Exception
     * @brief Custom exception class for flight data-related errors.
     *
     * This class extends std::runtime_error to provide specific error handling
     * within the FlightPath namespace.
     */
    class Exception : public std::runtime_error
    {
    public:
        /**
         * @brief Constructs a new FlightPath::Exception object.
         * @param what A description of the error.
         */
        Exception(const std::string &what);
    };

}

/**
 * @brief Formatter specialization for FlightPath::Exception.
 *
 * Enables the use of std::format with FlightPath::Exception, formatting
 * the exception using its what() message.
 */
template <>
struct std::formatter<FlightPath::Exception>
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
     * @brief  Formats the FlightPath::Exception object.
     * 
     * @param  obj The FlightPath::Exception instance to format.
     * @param  ctx The format context to write to.
     * @return     An iterator to the end of the output.
     */
    auto format(const FlightPath::Exception &obj, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "{}", obj.what());
    }

};
