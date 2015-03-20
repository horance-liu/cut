#ifndef HEA317698_FEF8_4B1B_AD3F_588C6A38F382
#define HEA317698_FEF8_4B1B_AD3F_588C6A38F382

#include <mango/infra/std/stdext.h>
#include <sstream>
#include <stdexcept>

STDEXT_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline T& __do_string_as(T& t, std::istringstream& stream)
{
    stream >> t;

    if (stream.fail())
        throw std::invalid_argument("Cannot convert parameter");

    return t;
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
T string_as(const std::string& s)
{
    T t;
    std::istringstream stream(s);

    return __do_string_as(t, stream);
}

////////////////////////////////////////////////////////////////////////////////
template<>
inline std::string string_as(const std::string& s)
{
    return s;
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
std::string to_string(T arg)
{
    std::stringstream s;
    s << arg;
    return s.str();
}

////////////////////////////////////////////////////////////////////////////////
std::string to_upper(const std::string& str);
std::string to_lower(const std::string& str);

////////////////////////////////////////////////////////////////////////////////
std::string trim(const std::string& str);
std::string ltrim(const std::string& str);
std::string rtrim(const std::string& str);

////////////////////////////////////////////////////////////////////////////////
#define __DO_STRINGIZE( symbol ) #symbol
#define STRINGIZE(symbol) __DO_STRINGIZE(symbol)

STDEXT_NS_END

#endif
