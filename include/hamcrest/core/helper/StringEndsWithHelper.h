#ifndef HBD05932F_59CA_4CC9_A56F_F98081F69BCD
#define HBD05932F_59CA_4CC9_A56F_F98081F69BCD

#include <hamcrest/core/matcher/StringEndsWith.h>

#define ends_with(postfix) HAMCREST_NS::StringEndsWith(false, postfix)
#define ends_with_ignoring_case(postfix) HAMCREST_NS::StringEndsWith(true, postfix)

#endif
