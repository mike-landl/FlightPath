#pragma once

#include <iostream>
#include <format>
#include <string_view>

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
    enum class Level
    {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    template <class ... Args>
    struct Print
    {
        Print(Level level, std::format_string<Args ...> msg, Args && ...args)
        {
            using namespace AnsiColor;
            
            std::string c = "?";
                 if (level == Level::DEBUG) { c = ColoredString<Color::BrightBlue  >("[D]"); }
            else if (level == Level::INFO ) { c = ColoredString<Color::BrightGreen >("[I]"); }
            else if (level == Level::WARN ) { c = ColoredString<Color::BrightYellow>("[W]"); }
            else if (level == Level::ERROR) { c = ColoredString<Color::BrightRed   >("[E]"); }
            
            if (level == Level::INFO)
            {
                // [LEVEL] MESSAGE (I'm not interestd where the message comes from if the log level is info)
                std::cout << std::format("{} {}", c, std::format(msg, std::forward<Args>(args) ...)) << "\n";
            }
            else
            {
                // [LEVEL] FILE:LINE MESSAGE
                std::cout << std::format("{} {}:{} {}", c, __FILE__, __LINE__, std::format(msg, std::forward<Args>(args) ...)) << "\n";
            }
        }
    };

    template <class ... Args>
    auto Info(std::format_string<Args ...> msg, Args && ...args) -> void
    {
        Print<Args...>(Level::INFO, msg, std::forward<Args>(args)...);
    }
}
