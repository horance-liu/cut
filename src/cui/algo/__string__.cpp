#include <cui/algo/__range__.h>
#include <cui/algo/__string__.h>

CUI_NS_BEGIN

namespace
{
    std::string toFixedSizedHexStr(unsigned int i)
    {
        std::stringstream oss;

        oss.flags (std::ios::hex);
        oss.fill('0');
        oss.width(2);

        oss << i;

        return oss.str();
    }

    std::string toFixedSizedHexStr(unsigned char val)
    {
        return toFixedSizedHexStr((unsigned int)val&0xFF);
    }
}

//////////////////////////////////////////
std::string toBufferString(void* buf, size_t size)
{
   std::stringstream oss;

   size_t sz = std::min(size, size_t(4));

   unsigned char* p = (unsigned char*)buf;

   oss << "[";

   for(size_t i=0; i < sz; i++)
   {
      oss << toFixedSizedHexStr(p[i]);
      if(i != sz - 1)
      {
         oss << " ";
      }
   }

   if(size > size_t(4))
   {
      oss << " ...";
   }

   oss << "]";

   return oss.str();
}

//////////////////////////////////////////
std::string toPointerString(void* p)
{
    if(p == 0) return "nil";

    std::stringstream oss;

    oss << "0x";

    oss.flags (std::ios::hex);
    oss.fill('0');
    oss.width(8);

    oss << reinterpret_cast<unsigned long>(p);

    return oss.str();
}

//////////////////////////////////////////
std::string toString(const std::nullptr_t& p)
{
    return "nullptr";
}

//////////////////////////////////////////
std::string toString(const std::string& s)
{
    std::stringstream oss;
    oss << s;
    return oss.str();
}

//////////////////////////////////////////
std::string toString(char* s)
{
    std::stringstream oss;

    if(s == 0)
        oss << "nil";
    else
        oss << s;

    return oss.str();
}

//////////////////////////////////////////
std::string toString(const char* s)
{  return toString(const_cast<char*>(s)); }

//////////////////////////////////////////
std::string toString(bool b)
{
    std::stringstream oss;
    oss << (b ? "true" : "false");
    return oss.str();
}

namespace
{
    template <typename T>
    std::string toValStr(T val)
    {
        std::stringstream oss;

        oss.flags(std::ios::fixed);
        oss.precision(2);

        oss << val;
        return oss.str();
    }

    std::string toValStr(char val)
    { return toValStr((int)val); }

    std::string toValStr(signed char val)
    { return toValStr((int)val); }

    std::string toValStr(unsigned char val)
    { return toValStr((unsigned int)val); }
}

std::string toString(char c)
{ return toValStr(c); }

std::string toString(signed char c)
{ return toValStr(c); }

std::string toString(unsigned char c)
{ return toValStr(c); }

std::string toString(short s)
{ return toValStr(s); }

std::string toString(unsigned short s)
{ return toValStr(s); }

std::string toString(int i)
{ return toValStr(i); }

std::string toString(unsigned int i)
{ return toValStr(i); }

std::string toString(long l)
{ return toValStr(l); }

std::string toString(unsigned long l)
{ return toValStr(l); }

std::string toString(float f)
{ return toValStr(f); }

std::string toString(double f)
{ return toValStr(f); }

std::string toString(long double d)
{ return toValStr(d); }

std::string to_upper(const std::string& str)
{
    return CUI_NS::reduce(str, std::string(),
            [](std::string& result, char c) { return result += toupper(c); });
}

std::string to_lower(const std::string& str)
{
    return CUI_NS::reduce(str, std::string(),
            [](std::string& result, char c) { return result += tolower(c); });
}

namespace
{
    const std::string& space()
    {
        static const std::string s = " \n\r\t";
        return s;
    }
}

std::string ltrim(const std::string& str)
{
    auto begin = str.find_first_not_of(space());
    return begin == std::string::npos ? str : str.substr(begin);
}

std::string rtrim(const std::string& str)
{
    auto end = str.find_last_not_of(space());
    return end == std::string::npos ? str : str.substr(0, end + 1);
}

std::string trim(const std::string& str)
{
    return rtrim(ltrim(str));
}

CUI_NS_END
