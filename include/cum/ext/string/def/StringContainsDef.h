#ifndef HFDE31C8C_FA16_4508_BCCE_9AFE933D7270
#define HFDE31C8C_FA16_4508_BCCE_9AFE933D7270

#include <cum/ext/string/matcher/StringContains.h>

CUM_NS_BEGIN

inline StringContains* contains_string(const std::string& substring)
{
    return new StringContains(false, substring);
}

inline StringContains* contains_string_ignoring_case(const std::string& substring)
{
    return new StringContains(true, substring);
}

CUM_NS_END

#endif
