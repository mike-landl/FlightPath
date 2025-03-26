#include "Exception.hpp"

namespace FlightData
{
    Exception::Exception(const std::string &what)
        : std::runtime_error(what)
    {
    }
}
