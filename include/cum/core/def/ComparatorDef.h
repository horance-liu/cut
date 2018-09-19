#ifndef HDFBDF617_D256_4ACA_A294_8F5558BD74ACGGG
#define HDFBDF617_D256_4ACA_A294_8F5558BD74ACGGG

#include <cum/core/matcher/comparator/IsEqual.h>
#include <cum/core/matcher/comparator/IsNotEqual.h>
#include <cum/core/matcher/comparator/IsLessThan.h>
#include <cum/core/matcher/comparator/IsGreaterThan.h>
#include <cum/core/matcher/comparator/IsGreaterThanOrEqualTo.h>
#include <cum/core/matcher/comparator/IsLessThanOrEqualTo.h>

#define DEFINE_COMPARATOR(factory, comparator)                          \
template <typename T>                                                   \
inline CUM_NS::comparator<T>* factory(const T& expected)           \
{                                                                       \
    return new CUM_NS::comparator<T>(expected);                    \
}                                                                       \
template <typename T>                                                   \
inline CUM_NS::comparator<const T*>* factory(const T expected[])   \
{                                                                       \
    return new CUM_NS::comparator<const T*>(expected);             \
}

CUM_NS_BEGIN

DEFINE_COMPARATOR(eq, IsEqual)
DEFINE_COMPARATOR(ne, IsNotEqual)
DEFINE_COMPARATOR(lt, IsLessThan)
DEFINE_COMPARATOR(gt, IsGreaterThan)
DEFINE_COMPARATOR(le, IsLessThanOrEqualTo)
DEFINE_COMPARATOR(ge, IsGreaterThanOrEqualTo)

CUM_NS_END

#endif
