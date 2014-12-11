#ifndef H5E9E7C61_DCDA_4893_93D2_F8B6BA190E86
#define H5E9E7C61_DCDA_4893_93D2_F8B6BA190E86

#include <hamcrest/core/matcher/SubstringMatcher.h>

HAMCREST_NS_BEGIN

struct StringEndsWith : SubstringMatcher
{
    StringEndsWith(bool ignoringCase, const std::string& substring);

private:
    OVERRIDE(bool evalSubstringOf(const std::string&) const);
    OVERRIDE(const StringEndsWith* clone() const);
};

HAMCREST_MATCHER_TAG(StringEndsWith, std::string);

HAMCREST_NS_END

#endif
