#pragma once

#include <iostream>
#include <format>
#include <string_view>
#include <source_location>

#include "Exception.hpp"
#include "Types.hpp"

/**
 * @namespace AnsiColor
 * @brief Contains utilities for applying ANSI color codes to strings.
 */
namespace AnsiColor
{
    /**
     * @brief Enum class representing ANSI color types.
     */
    enum class Color
    {
        Reset,          ///< Reset to default color.
        BrightBlue,     ///< Bright blue color.
        BrightGreen,    ///< Bright green color.
        BrightYellow,   ///< Bright yellow color.
        BrightRed       ///< Bright red color.
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

/**
 * @namespace FlightPath::Log
 * @brief Provides a simple logging system with support for colored log levels and source location info.
 */
namespace FlightPath::Log
{
    using namespace AnsiColor;

    /**
     * @brief Log levels used in the logging system.
     */
    enum class Level
    {
        DEBUG,  ///< Debug level, typically used for development details.
        INFO,   ///< Informational messages.
        WARN,   ///< Warnings about potentially problematic situations.
        ERROR   ///< Error messages indicating failures.
    };

    /**
     * @brief Returns a colored prefix string for the specified log level.
     * 
     * @tparam L The log level.
     * @return A colored prefix string (e.g., "[D]" for DEBUG).
     * @throws Exception If an unsupported log level is specified.
     */
    template<Level L>
    inline auto constexpr GetColoredPrefix() -> std::string
    {
             if constexpr (L == Level::DEBUG) { return ColoredString<Color::BrightBlue  >("[D]"); }
        else if constexpr (L == Level::INFO ) { return ColoredString<Color::BrightGreen >("[I]"); }
        else if constexpr (L == Level::WARN ) { return ColoredString<Color::BrightYellow>("[W]"); }
        else if constexpr (L == Level::ERROR) { return ColoredString<Color::BrightRed   >("[E]"); }
        else { throw Exception(std::format("No colored prefix for Log::Level {} implemented.", static_cast<i32>(L))); }
    }

    /**
     * @brief Logs a message to standard output with a prefix and optional source location.
     * 
     * @tparam L The log level.
     * @param message The message to log.
     * @param location The source location of the log call (defaults to caller location).
     */
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
            // only use file name (without path)
            std::string_view file = location.file_name();
            size_t pos = file.find_last_of("/\\");
            if (pos != std::string_view::npos)
            {
                file.remove_prefix(pos + 1);
            }

            std::cout << std::format("{} {}:{} {}", prefix, file, location.line(), message) << "\n";
        }
    }

    /**
     * @brief Logs a DEBUG-level message with optional source location.
     * 
     * @param message The debug message.
     * @param location The source location of the log call (defaults to caller location).
     */
    inline auto Debug(std::string_view message, const std::source_location& location = std::source_location::current()) -> void
    {
        LogMessage<Level::DEBUG>(message, location);
    }

    /**
     * @brief Logs an INFO-level message.
     * 
     * @param message The informational message.
     * @param location The source location of the log call (defaults to caller location).
     */
    inline auto Info(std::string_view message, const std::source_location& location = std::source_location::current()) -> void
    {
        LogMessage<Level::INFO>(message, location);
    }

    /**
     * @brief Logs a WARN-level message with optional source location.
     * 
     * @param message The warning message.
     * @param location The source location of the log call (defaults to caller location).
     */
    inline auto Warn(std::string_view message, const std::source_location& location = std::source_location::current()) -> void
    {
        LogMessage<Level::WARN>(message, location);
    }

    /**
     * @brief Logs an ERROR-level message with optional source location.
     * 
     * @param message The error message.
     * @param location The source location of the log call (defaults to caller location).
     */
    inline auto Error(std::string_view message, const std::source_location& location = std::source_location::current()) -> void
    {
        LogMessage<Level::ERROR>(message, location);
    }
}
