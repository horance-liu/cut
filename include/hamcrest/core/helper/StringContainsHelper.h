#ifndef HFDE31C8C_FA16_4508_BCCE_9AFE933D7270
#define HFDE31C8C_FA16_4508_BCCE_9AFE933D7270

#include <hamcrest/core/matcher/StringContains.h>

#define contains_string(substring) HAMCREST_NS::StringContains(false, substring)
#define contains_string_ignoring_case(substring) HAMCREST_NS::StringContains(true, substring)

#endif
