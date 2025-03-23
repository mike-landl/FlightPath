#pragma once

#include <source_location>
#include <print>
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

    template <Level L, class ... Args>
    struct print
    {
    
    };

    template <Level level, class ... Args>
    struct print<level, const char *, Args ...>
    {
        print(const char *msg, Args && ...args, std::source_location loc = std::source_location::current())
        {
            using namespace AnsiColor;

            std::string c = "?";
                 if constexpr (level==Level::DEBUG) { c = ColoredString<Color::BrightBlue  >("[D]"); }
            else if constexpr (level==Level::INFO ) { c = ColoredString<Color::BrightGreen >("[I]"); }
            else if constexpr (level==Level::WARN ) { c = ColoredString<Color::BrightYellow>("[W]"); }
            else if constexpr (level==Level::ERROR) { c = ColoredString<Color::BrightRed   >("[E]"); }

            // only use file name (without path)
            std::string_view file = loc.file_name();
            size_t pos = file.find_last_of("/\\");
            if (pos != std::string_view::npos)
            {
                file.remove_prefix(pos + 1);
            }
            
            if constexpr (level==Level::INFO)
            {
                // [LEVEL] MESSAGE (I'm not interestd where the message comes from if the log level is info)
                std::println("{} {}", c, std::vformat(msg, std::make_format_args(args ...)));
            }
            else
            {
                // [LEVEL] FILE:LINE MESSAGE
                std::println("{} {}:{} {}", c, file, loc.line(), std::vformat(msg, std::make_format_args(args ...)));
            }
        }
    };

    template <Level level, class ... args>
    print(args ...) -> print<level, args ...>;

    template <class ... args> using Debug = print<Level::DEBUG, args ...>;
    template <class ... args> using Info  = print<Level::INFO,  args ...>;
    template <class ... args> using Warn  = print<Level::WARN,  args ...>;
    template <class ... args> using Error = print<Level::ERROR, args ...>;
}
