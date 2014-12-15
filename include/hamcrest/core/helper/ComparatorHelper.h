#ifndef HDFBDF617_D256_4ACA_A294_8F5558BD74AC
#define HDFBDF617_D256_4ACA_A294_8F5558BD74AC

#include <hamcrest/core/matcher/comparator/IsEqual.h>
#include <hamcrest/core/matcher/comparator/IsNotEqual.h>
#include <hamcrest/core/matcher/comparator/IsLessThan.h>
#include <hamcrest/core/matcher/comparator/IsGreaterThan.h>
#include <hamcrest/core/matcher/comparator/IsLessThanOrEqualTo.h>
#include <hamcrest/core/matcher/comparator/IsGreaterThanOrEqualTo.h>

#define DEFINE_COMPARATOR(dsl_t, comparator_t)                       \
template <typename T>                                                \
const HAMCREST_NS::comparator_t<T> dsl_t(const T& expected)          \
{                                                                    \
    return HAMCREST_NS::comparator_t<T>(expected);                   \
}                                                                    \
/* commonly occurs with string literals */                           \
template <typename T>                                                \
const HAMCREST_NS::comparator_t<const T*> dsl_t(const T expected[])  \
{                                                                    \
    return HAMCREST_NS::comparator_t<const T*>(expected);            \
}

DEFINE_COMPARATOR(equal_to, IsEqual)
DEFINE_COMPARATOR(not_equal_to, IsNotEqual)
DEFINE_COMPARATOR(less_than, IsLessThan)
DEFINE_COMPARATOR(greater_than, IsGreaterThan)
DEFINE_COMPARATOR(less_than_or_equal_to, IsLessThanOrEqualTo)
DEFINE_COMPARATOR(greater_than_or_equal_to, IsGreaterThanOrEqualTo)

#endif
