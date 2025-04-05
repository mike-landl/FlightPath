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
