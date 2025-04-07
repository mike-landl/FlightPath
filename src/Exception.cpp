#include "Exception.hpp"

namespace FlightPath
{
    Exception::Exception(const std::string &what)
        : std::runtime_error(what)
    {
    }
}
