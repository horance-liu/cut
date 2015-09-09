#include "magellan/except/AssertionError.h"
#include <sstream>

MAGELLAN_NS_BEGIN

AssertionError::AssertionError(const std::string& source, const std::string& msg)
    : msg(source+msg)
{
}

const char* AssertionError::what() const noexcept
{
    return msg.c_str();
}

MAGELLAN_NS_END
