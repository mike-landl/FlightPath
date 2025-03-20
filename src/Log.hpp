#pragma once

#include <source_location>
#include <print>

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

    template <Level L, class ... Args>
    struct print<L, const char *, Args ...>
    {
        print(const char *msg, Args && ...args, std::source_location loc = std::source_location::current())
        {
            auto c = "?";
                 if constexpr (L==Level::DEBUG) { c = "\x1B[94m[D]\033[0m"; } // bright blue   [D]
            else if constexpr (L==Level::INFO ) { c = "\x1B[92m[I]\033[0m"; } // bright green  [I]
            else if constexpr (L==Level::WARN ) { c = "\x1B[93m[W]\033[0m"; } // bright yellow [W]
            else if constexpr (L==Level::ERROR) { c = "\x1B[91m[E]\033[0m"; } // bright red    [E]

            // only use file name (without path)
            std::string_view file = loc.file_name();
            size_t pos = file.find_last_of("/\\");
            if (pos != std::string_view::npos)
            {
                file.remove_prefix(pos + 1);
            }
            // print a line with [LEVEL] FILE:LINE MESSAGE
            std::println("{} {}:{} {}", c, file, loc.line(), std::vformat(msg, std::make_format_args(args ...)));
        }
    };

    template <Level level, class ... args>
    print(args ...) -> print<level, args ...>;

    template <class ... args> using Debug = print<Level::DEBUG, args ...>;
    template <class ... args> using Info  = print<Level::INFO,  args ...>;
    template <class ... args> using Warn  = print<Level::WARN,  args ...>;
    template <class ... args> using Error = print<Level::ERROR, args ...>;

}