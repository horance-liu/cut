#ifndef HBD05932F_59CA_4CC9_A56F_F98081F69BCD
#define HBD05932F_59CA_4CC9_A56F_F98081F69BCD

#include <hamcrest/core/StringEndsWith.h>

HAMCREST_NS_BEGIN

#define ends_with(prefix) HAMCREST_NS::StringEndsWith(false, prefix)
#define ends_with_ignoring_case(prefix) HAMCREST_NS::StringEndsWith(true, prefix)

HAMCREST_NS_END

#endif
