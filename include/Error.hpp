#pragma once

#include <format>
#include <string_view>
#include <utility>

#include "Exception.hpp"

namespace FlightData
{
    /**
     * @brief Throws an exception if the required condition is false.
     *
     * This function checks the given requirement and throws a FlightData::Exception
     * with a formatted message if the requirement evaluates to false.
     *
     * @tparam Args         Variadic template parameters for format arguments of msg.
     * @param  requirement  The condition to check.
     * @param  msg          The format string used for the exception message.
     * @param  args         The arguments to insert into the msg format string.
     *
     * @throws FlightData::Exception if predicate is false.
     */
    template<class ... Args>
    inline auto Ensure(bool requirement, std::string_view msg, Args && ... args) -> void
    {
        if(!requirement)
        {
            throw Exception(std::vformat(msg, std::make_format_args(std::forward<Args>(args) ...)));
        }
    }
    
}
