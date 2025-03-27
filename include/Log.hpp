#pragma once

#include <iostream>
#include <format>
#include <string_view>
#include <source_location>

#include "Exception.hpp"
#include "Types.hpp"

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
    inline auto constexpr ToAnsiCode() -> std::string
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
    inline auto constexpr ColoredString(std::string_view str) -> std::string
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

    template<Level L>
    inline auto constexpr GetColoredPrefix() -> std::string
    {
             if constexpr (L == Level::DEBUG) { return ColoredString<Color::BrightBlue  >("[D]"); }
        else if constexpr (L == Level::INFO ) { return ColoredString<Color::BrightGreen >("[I]"); }
        else if constexpr (L == Level::WARN ) { return ColoredString<Color::BrightYellow>("[W]"); }
        else if constexpr (L == Level::ERROR) { return ColoredString<Color::BrightRed   >("[E]"); }
        else { throw Exception(std::format("No colored prefix for Log::Level {} implemented.", static_cast<i32>(L))); }
    }

    template <Level L>
    inline auto LogMessage(std::string_view message, const std::source_location& location = std::source_location::current())
    {
        std::string prefix = GetColoredPrefix<L>();

        if constexpr (L == Level::INFO)
        {
            std::cout << std::format("{} {}", prefix, message) << "\n";
        }
        else
        {
            std::cout << std::format("{} {}:{} {}", prefix, location.file_name(), location.line(), message) << "\n";
        }
    }

    inline auto Debug(std::string_view message, const std::source_location& location = std::source_location::current()) -> void
    {
        LogMessage<Level::DEBUG>(message, location);
    }

    inline auto Info(std::string_view message, const std::source_location& location = std::source_location::current()) -> void
    {
        LogMessage<Level::INFO>(message, location);
    }

    inline auto Warn(std::string_view message, const std::source_location& location = std::source_location::current()) -> void
    {
        LogMessage<Level::WARN>(message, location);
    }

    inline auto Error(std::string_view message, const std::source_location& location = std::source_location::current()) -> void
    {
        LogMessage<Level::ERROR>(message, location);
    }
}
