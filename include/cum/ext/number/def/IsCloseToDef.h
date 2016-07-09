#ifndef HEB929F20_4001_4DDD_9644_E5019D3A266B
#define HEB929F20_4001_4DDD_9644_E5019D3A266B

#include <cum/ext/number/matcher/IsCloseTo.h>

CUM_NS_BEGIN

inline IsCloseTo* close_to(long double value, long double delta)
{
    return new IsCloseTo(value, delta);
}

CUM_NS_END



#endif
