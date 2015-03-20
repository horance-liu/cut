#include <magellan/hamcrest/ext/string/matcher/StringContains.h>
#include <string.h>

HAMCREST_NS_BEGIN

StringContains::StringContains(bool ignoringCase, const std::string& substring)
    : SubstringMatcher("containing", substring, ignoringCase)
{
}

bool StringContains::evalSubstringOf(const std::string& str) const
{
    auto &&target = converted(substring);

    auto s = str.c_str();
    auto len = str.size() - target.size() + 1;
    for(auto i=0; i < len; i++)
    {
       if(::strncmp(&s[i], target.c_str(), target.size()) == 0)
       {
          return true;
       }
    }

    return false;
}

const StringContains* StringContains::clone() const
{
    return new StringContains(ignoringCase, substring);
}

HAMCREST_NS_END
