#include <hamcrest/core/matcher/StringEndsWith.h>

HAMCREST_NS_BEGIN

StringEndsWith::StringEndsWith(bool ignoringCase, const std::string& substring)
    : SubstringMatcher("ending with", substring, ignoringCase)
{
}

bool StringEndsWith::evalSubstringOf(const std::string& str) const
{
    auto &&target = converted(substring);
    return ::strncmp( str.c_str() + str.size() - target.size()
                    , target.c_str()
                    , target.size()) == 0;
}

const StringEndsWith* StringEndsWith::clone() const
{
    return new StringEndsWith(ignoringCase, substring);
}

HAMCREST_NS_END
