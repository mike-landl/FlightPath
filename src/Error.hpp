#pragma once

#include <format>
#include <string_view>
#include <utility>

#include "Exception.hpp"

namespace FlightData
{

    template<class ... Args>
    inline auto Ensure(bool predicate, std::string_view msg, Args && ... args) -> void
    {
        if(!predicate)
        {
            throw Exception(std::vformat(msg, std::make_format_args(std::forward<Args>(args) ...)));
        }
    }
    
}
