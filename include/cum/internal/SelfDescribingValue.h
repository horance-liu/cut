#ifndef H28C48B23_1C42_412E_B878_F54AC7C7DCA7
#define H28C48B23_1C42_412E_B878_F54AC7C7DCA7

#include <cum/base/SelfDescribing.h>

CUM_NS_BEGIN

struct Description;

template <typename T>
struct SelfDescribingValue : SelfDescribing
{
    explicit SelfDescribingValue(const T& value)
        : value(value)
    {}

private:
    __OVERRIDE__(void describeTo(Description& desc) const); // don't implement.

private:
    const T value;
};

CUM_NS_END

#endif
