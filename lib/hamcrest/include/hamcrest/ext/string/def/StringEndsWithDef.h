#ifndef HBD05932F_59CA_4CC9_A56F_F98081F69BCD
#define HBD05932F_59CA_4CC9_A56F_F98081F69BCD

#include <hamcrest/ext/string/matcher/StringEndsWith.h>

HAMCREST_NS_BEGIN

inline StringEndsWith* ends_with(const std::string& postfix)
{
    return new StringEndsWith(false, postfix);
}

inline StringEndsWith* ends_with_ignoring_case(const std::string& postfix)
{
    return new StringEndsWith(true, postfix);
}

HAMCREST_NS_END

#endif
