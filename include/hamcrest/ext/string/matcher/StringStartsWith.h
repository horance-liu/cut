#ifndef H044CD3FB_447C_48A9_8931_A6DD2578C0CA
#define H044CD3FB_447C_48A9_8931_A6DD2578C0CA

#include <hamcrest/ext/string/matcher/SubstringMatcher.h>

HAMCREST_NS_BEGIN

struct StringStartsWith : SubstringMatcher
{
    StringStartsWith(bool ignoringCase, const std::string& substring);

private:
    OVERRIDE(bool evalSubstringOf(const std::string&) const);
    OVERRIDE(const StringStartsWith* clone() const);
};

HAMCREST_MATCHER_TAG(StringStartsWith, std::string);

HAMCREST_NS_END

#endif
