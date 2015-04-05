#include <hamcrest/ext/string/matcher/StringEndsWith.h>
#include <string.h>

HAMCREST_NS_BEGIN

StringEndsWith::StringEndsWith(bool ignoringCase, const std::string& substring)
    : StringMatcher("ending with", substring, ignoringCase)
{
}

bool StringEndsWith::evalOf(const std::string& str) const
{
    return ::strncmp( str.c_str() + str.size() - expected.size()
                    , expected.c_str()
                    , expected.size()) == 0;
}

HAMCREST_NS_END
