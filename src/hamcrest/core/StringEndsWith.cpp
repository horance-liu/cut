#include <hamcrest/core/StringEndsWith.h>

HAMCREST_NS_BEGIN

StringEndsWith::StringEndsWith(bool ignoringCase, const std::string& substring)
    : SubstringMatcher("ending with", substring, ignoringCase)
{
}

bool StringEndsWith::evalSubstringOf(const std::string& s) const
{
    return ::strncmp(converted(s).c_str() + s.size() - substring.size()
    , converted(substring).c_str(), substring.size()) == 0;
}

const StringEndsWith* StringEndsWith::clone() const
{
    return new StringEndsWith(ignoringCase, substring);
}

HAMCREST_NS_END
