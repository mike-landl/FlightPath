#include "Exception.hpp"

namespace FlightData
{

    Exception::Exception(const std::string &what, std::uint32_t skip)
        : std::runtime_error(what)
        , trace_(std::stacktrace::current(skip))
    {
    }

    auto Exception::Stacktrace() const -> std::string
    {
        return std::to_string(trace_);
    }
}
