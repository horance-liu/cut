#include <cut/except/AssertionError.h>
#include <sstream>

CUT_NS_BEGIN

AssertionError::AssertionError(const std::string& source, const std::string& msg)
    : msg(source+msg)
{
}

const char* AssertionError::what() const noexcept
{
    return msg.c_str();
}

CUT_NS_END
