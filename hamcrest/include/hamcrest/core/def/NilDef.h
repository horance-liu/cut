#ifndef H46B05CEF_B52F_4968_A388_D503B5604490
#define H46B05CEF_B52F_4968_A388_D503B5604490

#include <hamcrest/core/matcher/atomic/IsNil.h>

HAMCREST_NS_BEGIN

inline IsNil* nil() { return new IsNil; }

HAMCREST_NS_END

#endif
