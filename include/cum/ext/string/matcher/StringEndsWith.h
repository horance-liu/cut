#ifndef H5E9E7C61_DCDA_4893_93D2_F8B6BA190E86
#define H5E9E7C61_DCDA_4893_93D2_F8B6BA190E86

#include <cum/ext/string/matcher/StringMatcher.h>

CUM_NS_BEGIN

struct StringEndsWith : StringMatcher
{
    StringEndsWith(bool ignoringCase, const std::string& substring);

private:
    __OVERRIDE__(bool evalOf(const std::string&) const);
};

CUM_MATCHER_TAG(StringEndsWith, std::string);

CUM_NS_END

#endif
