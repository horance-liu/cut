#include <hamcrest/ext/string/matcher/StringContains.h>
#include <string.h>

HAMCREST_NS_BEGIN

StringContains::StringContains(bool ignoringCase, const std::string& substring)
    : StringMatcher("containing", substring, ignoringCase)
{
}

bool StringContains::evalOf(const std::string& str) const
{
    auto s = str.c_str();
    auto len = str.size() - expected.size() + 1;

    for(auto i=0; i < len; i++)
    {
       if(::strncmp(&s[i], expected.c_str(), expected.size()) == 0)
       {
          return true;
       }
    }

    return false;
}

HAMCREST_NS_END
