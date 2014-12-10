#ifndef HDFBDF617_D256_4ACA_A294_8F5558BD74AC
#define HDFBDF617_D256_4ACA_A294_8F5558BD74AC

#include <hamcrest/core/IsEqual.h>

HAMCREST_NS_BEGIN

template <typename T>
const IsEqual<T> equal_to(const T& expected)
{
    return IsEqual<T>(expected);
}

// convert matcher<T[]> to matcher<T*>
template <typename T>
const IsEqual<const T*> equal_to(const T expected[])
{
    return IsEqual<const T*>(expected);
}

HAMCREST_NS_END

#endif
