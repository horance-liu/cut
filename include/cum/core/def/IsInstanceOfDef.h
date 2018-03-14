#ifndef HEBFD7990_C9E9_4D78_A023_14F4A652A145
#define HEBFD7990_C9E9_4D78_A023_14F4A652A145

#include <cum/cum.h>

CUM_NS_BEGIN

template <typename Base, typename T>
inline bool instanceof(const T& t)
{
    return dynamic_cast<const Base*>(&t) != nullptr;
}

CUM_NS_END

#endif
