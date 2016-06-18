#ifndef H1BEBC79D_5BA8_4F6C_AD8C_94F820EC7D5B
#define H1BEBC79D_5BA8_4F6C_AD8C_94F820EC7D5B

#include <ccinfra/ccinfra.h>
#include <ccinfra/base/BaseTypes.h>

CCINFRA_NS_BEGIN

template <typename T>
T bit_mask(U32 bitNum)
{
    return ((T)1 << bitNum) - 1;
}

template <typename T>
T bit_value(T target, U32 offset, U32 length)
{
    return (target >> offset) & bit_mask<T>(length);
}

template <typename T>
bool is_bit_on(T target, U32 offset)
{
    return bit_value<T>(target, offset, 1) > 0;
}

#define BIT_MASK(BIT_NUM)       (((U64)1 << BIT_NUM) - 1)

#define GET_BITS_VALUE(target, offset, length) (((target) >> (offset)) & BIT_MASK(length))

#define IS_BIT_ON(target, offset) (GET_BITS_VALUE(target, offset, 1) > 0)

CCINFRA_NS_END

#endif
