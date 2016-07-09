#ifndef H81110271_991D_4024_B460_602F5FD78CF3
#define H81110271_991D_4024_B460_602F5FD78CF3

#include <cum/ext/string/matcher/StringMatcher.h>

CUM_NS_BEGIN

struct StringContains : StringMatcher
{
    StringContains(bool ignoringCase, const std::string& substring);

private:
    __OVERRIDE__(bool evalOf(const std::string&) const);
};

CUM_MATCHER_TAG(StringContains, std::string);

CUM_NS_END

#endif
