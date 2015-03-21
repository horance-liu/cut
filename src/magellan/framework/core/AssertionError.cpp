#include "magellan/framework/core/AssertionError.h"
#include <sstream>

MAGELLAN_NS_BEGIN

AssertionError::AssertionError(const std::string& source, const std::string& msg)
    : source(source), msg(msg)
{}

const char* AssertionError::what() const noexcept
{
    std::stringstream ss;
    ss << source << ":" << msg;
    return ss.str().c_str();
}

MAGELLAN_NS_END
