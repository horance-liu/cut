#include <cum/ext/string/matcher/StringContains.h>
#include <string.h>

CUM_NS_BEGIN

StringContains::StringContains(bool ignoringCase, const std::string& substring)
    : StringMatcher(ignoringCase, "containing", substring)
{
}

bool StringContains::evalOf(const std::string& str) const
{
    return str.find(expected) != std::string::npos;
}

CUM_NS_END
