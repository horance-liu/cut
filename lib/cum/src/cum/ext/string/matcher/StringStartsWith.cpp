#include <cum/ext/string/matcher/StringStartsWith.h>
#include <string.h>

CUM_NS_BEGIN

StringStartsWith::StringStartsWith(bool ignoringCase, const std::string& substring)
    : StringMatcher(ignoringCase, "starting with", substring)
{
}

bool StringStartsWith::evalOf(const std::string& str) const
{
    return str.length() >= expected.length() &&
      str.compare(0, expected.length(), expected) == 0;
}

CUM_NS_END
