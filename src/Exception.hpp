#pragma once

#include <stdexcept>
#include <cstdint>
#include <string>

#include <format>

namespace FlightData
{
    class Exception : public std::runtime_error
    {
    public:
        Exception(const std::string &what, std::uint32_t skip = 1u);
    };

}

template <>
struct std::formatter<FlightData::Exception>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::begin(ctx);
    }

    auto format(const FlightData::Exception &obj, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "{}", obj.what());
    }

};
