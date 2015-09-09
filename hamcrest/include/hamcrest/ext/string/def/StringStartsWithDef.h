#ifndef H22AE9E32_9055_406A_BF9F_7420F3A227EA
#define H22AE9E32_9055_406A_BF9F_7420F3A227EA

#include <hamcrest/ext/string/matcher/StringStartsWith.h>

HAMCREST_NS_BEGIN

inline StringStartsWith* starts_with(const std::string& prefix)
{
    return new StringStartsWith(false, prefix);
}

inline StringStartsWith* starts_with_ignoring_case(const std::string& prefix)
{
    return new StringStartsWith(true, prefix);
}

HAMCREST_NS_END

#endif
