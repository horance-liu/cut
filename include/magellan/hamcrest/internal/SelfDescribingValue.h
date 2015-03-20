#ifndef H28C48B23_1C42_412E_B878_F54AC7C7DCA7
#define H28C48B23_1C42_412E_B878_F54AC7C7DCA7

#include <magellan/hamcrest/base/SelfDescribing.h>

HAMCREST_NS_BEGIN

struct Description;

template <typename T>
struct SelfDescribingValue : SelfDescribing
{
    explicit SelfDescribingValue(const T& value)
        : value(value)
    {}

private:
    OVERRIDE(void describeTo(Description& desc) const); // don't implement.

private:
    const T value;
};

HAMCREST_NS_END

#endif
