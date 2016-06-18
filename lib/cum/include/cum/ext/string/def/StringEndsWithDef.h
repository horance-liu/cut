#ifndef HBD05932F_59CA_4CC9_A56F_F98081F69BCD
#define HBD05932F_59CA_4CC9_A56F_F98081F69BCD

#include <cum/ext/string/matcher/StringEndsWith.h>

CUM_NS_BEGIN

inline StringEndsWith* ends_with(const std::string& postfix)
{
    return new StringEndsWith(false, postfix);
}

inline StringEndsWith* ends_with_ignoring_case(const std::string& postfix)
{
    return new StringEndsWith(true, postfix);
}

CUM_NS_END

#endif
