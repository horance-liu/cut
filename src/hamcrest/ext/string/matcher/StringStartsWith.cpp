#include <hamcrest/ext/string/matcher/StringStartsWith.h>
#include <string.h>

HAMCREST_NS_BEGIN

StringStartsWith::StringStartsWith(bool ignoringCase, const std::string& substring)
    : StringMatcher("starting with", substring, ignoringCase)
{
}

bool StringStartsWith::evalOf(const std::string& str) const
{
    return ::strncmp(str.c_str(), expected.c_str(), expected.size()) == 0;
}

HAMCREST_NS_END
