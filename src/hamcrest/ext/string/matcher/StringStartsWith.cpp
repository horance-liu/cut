#include <hamcrest/ext/string/matcher/StringStartsWith.h>
#include <string.h>

HAMCREST_NS_BEGIN

StringStartsWith::StringStartsWith(bool ignoringCase, const std::string& substring)
    : SubstringMatcher("starting with", substring, ignoringCase)
{
}

bool StringStartsWith::evalSubstringOf(const std::string& str) const
{
    auto &&target = converted(substring);
    return ::strncmp(str.c_str(), target.c_str(), target.size()) == 0;
}

const StringStartsWith* StringStartsWith::clone() const
{
    return new StringStartsWith(ignoringCase, substring);
}

HAMCREST_NS_END
