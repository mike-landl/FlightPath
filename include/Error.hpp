#pragma once

#include <format>
#include <string_view>
#include <utility>

#include "Exception.hpp"

namespace FlightData
{
    /**
     * @brief Throws an exception if the predicate is false.
     *
     * This function checks the given predicate and throws a FlightData::Exception
     * with a formatted message if the predicate evaluates to false.
     *
     * @tparam Args Variadic template parameters for format arguments.
     * @param predicate The condition to check.
     * @param msg The format string used for the exception message.
     * @param args The arguments to format into the message.
     *
     * @throws FlightData::Exception if predicate is false.
     */
    template<class ... Args>
    inline auto Ensure(bool predicate, std::string_view msg, Args && ... args) -> void
    {
        if(!predicate)
        {
            throw Exception(std::vformat(msg, std::make_format_args(std::forward<Args>(args) ...)));
        }
    }
    
}
