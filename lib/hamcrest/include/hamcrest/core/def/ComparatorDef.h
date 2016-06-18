#ifndef HDFBDF617_D256_4ACA_A294_8F5558BD74ACGGG
#define HDFBDF617_D256_4ACA_A294_8F5558BD74ACGGG

#include <hamcrest/core/matcher/comparator/IsEqual.h>
#include <hamcrest/core/matcher/comparator/IsNotEqual.h>
#include <hamcrest/core/matcher/comparator/IsLessThan.h>
#include <hamcrest/core/matcher/comparator/IsGreaterThan.h>
#include <hamcrest/core/matcher/comparator/IsGreaterThanOrEqualTo.h>
#include <hamcrest/core/matcher/comparator/IsLessThanOrEqualTo.h>

#define DEFINE_COMPARATOR(factory, comparator)                          \
template <typename T>                                                   \
inline HAMCREST_NS::comparator<T>* factory(const T& expected)           \
{                                                                       \
    return new HAMCREST_NS::comparator<T>(expected);                    \
}                                                                       \
template <typename T>                                                   \
inline HAMCREST_NS::comparator<const T*>* factory(const T expected[])   \
{                                                                       \
    return new HAMCREST_NS::comparator<const T*>(expected);             \
}

DEFINE_COMPARATOR(eq, IsEqual)
DEFINE_COMPARATOR(ne, IsNotEqual)
DEFINE_COMPARATOR(lt, IsLessThan)
DEFINE_COMPARATOR(gt, IsGreaterThan)
DEFINE_COMPARATOR(le, IsLessThanOrEqualTo)
DEFINE_COMPARATOR(ge, IsGreaterThanOrEqualTo)

#endif
