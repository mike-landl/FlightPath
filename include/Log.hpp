#pragma once

#include <iostream>
#include <format>
#include <string_view>
#include <source_location>

namespace AnsiColor
{
    // @brief Enum class representing ANSI color types.
    enum class Color
    {
        Reset,
        BrightBlue,
        BrightGreen,
        BrightYellow,
        BrightRed
    };

    /** 
     * @brief Converts a `Color` enum to its corresponding ANSI escape code.
     * @tparam color The color to convert.
     * @return A string view containing the ANSI escape sequence for the given color.
     */
    template <Color color>
    inline constexpr auto ToAnsiCode() -> std::string_view
    {
        if      constexpr (color == Color::Reset)        return "\x1B[0m";
        else if constexpr (color == Color::BrightBlue)   return "\x1B[94m";
        else if constexpr (color == Color::BrightGreen)  return "\x1B[92m";
        else if constexpr (color == Color::BrightYellow) return "\x1B[93m";
        else if constexpr (color == Color::BrightRed)    return "\x1B[91m";
    }

    /**
     * @brief Wraps a string with ANSI color codes for the specified color.
     * @tparam color The color to apply.
     * @param  str   The input string to colorize.
     * @return A colored string using ANSI escape sequences.
     */
    template <Color color>
    inline auto ColoredString(std::string_view str) -> std::string
    {
        return std::format("{}{}{}", ToAnsiCode<color>(), str, ToAnsiCode<Color::Reset>());
    }
}

namespace FlightData::Log
{
    using namespace AnsiColor;

     // @brief Log levels used in the logging system.
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
