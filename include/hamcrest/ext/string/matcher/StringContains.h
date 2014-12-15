#ifndef H81110271_991D_4024_B460_602F5FD78CF3
#define H81110271_991D_4024_B460_602F5FD78CF3

#include <hamcrest/ext/string/matcher/SubstringMatcher.h>

HAMCREST_NS_BEGIN

struct StringContains : SubstringMatcher
{
    StringContains(bool ignoringCase, const std::string& substring);

private:
    OVERRIDE(bool evalSubstringOf(const std::string&) const);
    OVERRIDE(const StringContains* clone() const);
};

HAMCREST_MATCHER_TAG(StringContains, std::string);

HAMCREST_NS_END

#endif
