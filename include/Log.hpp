#pragma once

#include <iostream>
#include <format>
#include <string_view>
#include <source_location>

namespace AnsiColor
{
    enum class Color
    {
        Reset,
        BrightBlue,
        BrightGreen,
        BrightYellow,
        BrightRed
    };

    template <Color color>
    inline constexpr std::string_view ToAnsiCode()
    {
        if      constexpr (color == Color::Reset)        return "\x1B[0m";
        else if constexpr (color == Color::BrightBlue)   return "\x1B[94m";
        else if constexpr (color == Color::BrightGreen)  return "\x1B[92m";
        else if constexpr (color == Color::BrightYellow) return "\x1B[93m";
        else if constexpr (color == Color::BrightRed)    return "\x1B[91m";
    }

    template <Color color>
    inline std::string ColoredString(std::string_view str)
    {
        return std::format("{}{}{}", ToAnsiCode<color>(), str, ToAnsiCode<Color::Reset>());
    }
}

namespace FlightData::Log
{
    using namespace AnsiColor;

    enum class Level
    {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };


    inline auto Debug(std::string_view message, const std::source_location& location = std::source_location::current()) -> void
    {
        std::string prefix = ColoredString<Color::BrightBlue>("[D]");
        std::cout << std::format("{} {}:{} {}", prefix, location.file_name(), location.line(), message) << "\n";
    }

    inline auto Info(std::string_view message) -> void
    {
        std::string prefix = AnsiColor::ColoredString<AnsiColor::Color::BrightGreen>("[I]");
        std::cout << std::format("{} {}", prefix, message) << "\n";
    }

    inline auto Warn(std::string_view message, const std::source_location& location = std::source_location::current()) -> void
    {
        std::string prefix = ColoredString<Color::BrightYellow>("[W]");
        std::cout << std::format("{} {}:{} {}", prefix, location.file_name(), location.line(), message) << "\n";
    }

    inline auto Error(std::string_view message, const std::source_location& location = std::source_location::current()) -> void
    {
        std::string prefix = ColoredString<Color::BrightRed>("[E]");
        std::cout << std::format("{} {}:{} {}", prefix, location.file_name(), location.line(), message) << "\n";
    }
}
