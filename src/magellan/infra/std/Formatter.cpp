#include <magellan/infra/std/Formatter.h>

STDEXT_NS_BEGIN

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
    oss << "\"" << s << "\"";
    return oss.str();
}

//////////////////////////////////////////
std::string toString(char* s)
{
    std::stringstream oss;

    if(s == 0)
        oss << "nil";
    else
        oss << "\"" << s << "\"";

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

//////////////////////////////////////////
namespace
{
    template <typename T>
    std::string toHexStr(T val)
    {
        std::stringstream oss;
        oss.flags (std::ios::hex | std::ios::showbase);
        oss << val;
        return oss.str();
    }

    //////////////////////////////////////////
    std::string toHexStr(char val)
    { return toHexStr((int)val&0xFF); }

    //////////////////////////////////////////
    std::string toHexStr(signed char val)
    { return toHexStr((int)val&0xFF); }

    //////////////////////////////////////////
    std::string toHexStr(unsigned char val)
    { return toHexStr((unsigned int)val&0xFF); }

    //////////////////////////////////////////
    std::string toHexStr(short val)
    { return toHexStr((unsigned int)val&0xFFFF); }

    //////////////////////////////////////////
    std::string toHexStr(int val)
    { return toHexStr((unsigned int)val&0xFFFFFFFF); }

    //////////////////////////////////////////
    template <typename T>
    std::string toValStr(T val)
    {
        std::stringstream oss;
        oss << val;
        return oss.str();
    }

    //////////////////////////////////////////
    std::string toValStr(char val)
    { return toValStr((int)val); }

    //////////////////////////////////////////
    std::string toValStr(signed char val)
    { return toValStr((int)val); }

    //////////////////////////////////////////
    std::string toValStr(unsigned char val)
    { return toValStr((unsigned int)val); }

    //////////////////////////////////////////
    template <typename T>
    std::string toHexAndDecStr(T val)
    {
        std::stringstream oss;
        oss << toHexStr(val) << "/" << toValStr(val);
        return oss.str();
    }
}

//////////////////////////////////////////
std::string toString(char c)
{ return toHexAndDecStr(c); }

//////////////////////////////////////////
std::string toString(signed char c)
{ return toHexAndDecStr(c); }

//////////////////////////////////////////
std::string toString(unsigned char c)
{ return toHexAndDecStr(c); }

//////////////////////////////////////////
std::string toString(short s)
{ return toHexAndDecStr(s); }

//////////////////////////////////////////
std::string toString(unsigned short s)
{ return toHexAndDecStr(s); }

//////////////////////////////////////////
std::string toString(int i)
{ return toHexAndDecStr(i); }

//////////////////////////////////////////
std::string toString(unsigned int i)
{ return toHexAndDecStr(i); }

//////////////////////////////////////////
std::string toString(long l)
{ return toHexAndDecStr(l); }

//////////////////////////////////////////
std::string toString(unsigned long l)
{ return toHexAndDecStr(l); }

//////////////////////////////////////////
std::string toString(long long ll)
{ return toHexAndDecStr(ll); }

//////////////////////////////////////////
std::string toString(unsigned long long ll)
{ return toHexAndDecStr(ll); }

//////////////////////////////////////////
std::string toString(float f)
{ return toValStr(f); }

//////////////////////////////////////////
std::string toString(double f)
{ return toValStr(f); }

std::string toString(long double d)
{ return toValStr(d); }

STDEXT_NS_END
