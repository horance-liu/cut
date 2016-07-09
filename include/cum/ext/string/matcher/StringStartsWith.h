#ifndef H044CD3FB_447C_48A9_8931_A6DD2578C0CA
#define H044CD3FB_447C_48A9_8931_A6DD2578C0CA

#include <cum/ext/string/matcher/StringMatcher.h>

CUM_NS_BEGIN

struct StringStartsWith : StringMatcher
{
    StringStartsWith(bool ignoringCase, const std::string& substring);

private:
    __OVERRIDE__(bool evalOf(const std::string&) const);
};

CUM_MATCHER_TAG(StringStartsWith, std::string);

CUM_NS_END

#endif
