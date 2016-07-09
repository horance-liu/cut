#ifndef H119879C9_DC72_49BB_8576_5E8BF511AB0F
#define H119879C9_DC72_49BB_8576_5E8BF511AB0F

#include <cui/utils/__TypeName__.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <stddef.h>

CUI_NS_BEGIN

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
std::string toBufferString(void* buf, size_t size);
std::string toPointerString(void* buf);

////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::string toString(const T& val)
{
    return toBufferString((void*)&val, sizeof(val));
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::string toString(T* p)
{
    return toPointerString((void*)p);
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::string toString(const T* s)
{
    return toPointerString((void*)s);
}

////////////////////////////////////////////////////////////////////////////////
std::string toString(const std::string& s);
std::string toString(const std::nullptr_t& p);
std::string toString(char* s);
std::string toString(const char* s);
std::string toString(float f);
std::string toString(double d);
std::string toString(long double d);
std::string toString(bool b);
std::string toString(char c);
std::string toString(signed char c);
std::string toString(unsigned char c);
std::string toString(short s);
std::string toString(unsigned short s);
std::string toString(int i);
std::string toString(unsigned int i);
std::string toString(long l);
std::string toString(unsigned long l);

////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::string toTypeAndValueString(const T& val)
{
    std::stringstream oss;
    oss << toString(val) << ": " << TypeName<T>::value();
    return oss.str();
}

////////////////////////////////////////////////////////////////////////////////
std::string to_upper(const std::string& str);
std::string to_lower(const std::string& str);

////////////////////////////////////////////////////////////////////////////////
std::string trim(const std::string& str);
std::string ltrim(const std::string& str);
std::string rtrim(const std::string& str);

CUI_NS_END

#endif
