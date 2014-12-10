#include <hamcrest/core/StringStartsWith.h>
#include <string.h>

HAMCREST_NS_BEGIN

StringStartsWith::StringStartsWith(bool ignoringCase, const std::string& substring)
    : SubstringMatcher("starting with", substring, ignoringCase)
{
}

bool StringStartsWith::evalSubstringOf(const std::string& s) const
{
    return ::strncmp(converted(s).c_str(), converted(substring).c_str(), substring.size()) == 0;
}

const StringStartsWith* StringStartsWith::clone() const
{
    return new StringStartsWith(ignoringCase, substring);
}

HAMCREST_NS_END
