#ifndef _2DVU8M8O23OZD41ISGLSTT74N2VXXUSIWNTBSW7HQR3A662Z6BUW6XH7               
#define _2DVU8M8O23OZD41ISGLSTT74N2VXXUSIWNTBSW7HQR3A662Z6BUW6XH7

#include <cum/core/matcher/atomic/Anything.h>

CUM_NS_BEGIN

template <typename T>
inline Anything<T>* anything()
{
    return new Anything<T>;
}

#define _(type) CUM_NS::anything<type>()

CUM_NS_END

#endif
