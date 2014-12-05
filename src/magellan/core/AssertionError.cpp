#include <magellan/core/AssertionError.h>
#include <sstream>

MAGELLAN_NS_BEGIN

AssertionError::AssertionError
    ( const std::string& file, const int line, const std::string& msg)
    : file(file)
    , line(line)
    , msg(msg)
{
}

const char* AssertionError::what() const noexcept
{
    std::stringstream ss;
    ss << file << ":" << line << ":" << msg;
    return ss.str().c_str();
}

MAGELLAN_NS_END
