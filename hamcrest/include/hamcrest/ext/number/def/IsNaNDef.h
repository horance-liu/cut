#ifndef H748B4346_9478_4E9D_B5EA_271D5975986E
#define H748B4346_9478_4E9D_B5EA_271D5975986E

#include <hamcrest/ext/number/matcher/IsNaN.h>

HAMCREST_NS_BEGIN

inline IsNaN* nan() { return new IsNaN; }

HAMCREST_NS_END

#endif
