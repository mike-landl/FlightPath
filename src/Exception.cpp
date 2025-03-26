#include "Exception.hpp"

namespace FlightData
{
    Exception::Exception(const std::string &what, std::uint32_t skip)
        : std::runtime_error(what)
    {
    }
}
