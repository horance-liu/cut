#include <hamcrest/ext/string/matcher/StringEndsWith.h>
#include <string.h>

HAMCREST_NS_BEGIN

StringEndsWith::StringEndsWith(bool ignoringCase, const std::string& substring)
    : StringMatcher(ignoringCase, "ending with", substring)
{
}

bool StringEndsWith::evalOf(const std::string& str) const
{
    return str.length() >= expected.length() &&
      str.compare(str.length() - expected.length(), expected.length(), expected) == 0;
}

HAMCREST_NS_END
