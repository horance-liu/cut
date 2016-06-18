#ifndef HEC29B2BD_30CA_438A_B2EB_8309ED632ECA
#define HEC29B2BD_30CA_438A_B2EB_8309ED632ECA

#include <ccinfra/ccinfra.h>
#include <stddef.h>

CCINFRA_NS_BEGIN

template < typename KEY, size_t HASH_SIZE>
struct HashFn
{
};

inline size_t hash_string(const char* s)
{
    unsigned long __h = 0;
    for (; *s; ++s)
        __h = 5 * __h + *s;
    return size_t(__h);
}

template <size_t HASH_SIZE>
struct HashFn<char*, HASH_SIZE>
{
    size_t operator()(const char* s) const
    {
        return hash_string(s) % HASH_SIZE;
    }
};

template <size_t HASH_SIZE>
struct HashFn<const char*, HASH_SIZE>
{
    size_t operator()(const char* s) const
    {
        return hash_string(s) % HASH_SIZE;
    }
};

////////////////////////////////////////////////////
#define DEF_HASH_FN(TYPE)                       \
template <size_t HASH_SIZE>                     \
struct HashFn<TYPE, HASH_SIZE>                  \
{                                               \
    size_t operator()(TYPE x) const             \
    {                                           \
        return x % HASH_SIZE;                   \
    }                                           \
};

DEF_HASH_FN(char)
DEF_HASH_FN(unsigned char)
DEF_HASH_FN(signed char)

DEF_HASH_FN(short)
DEF_HASH_FN(unsigned short)

DEF_HASH_FN(int)
DEF_HASH_FN(unsigned int)

DEF_HASH_FN(long)
DEF_HASH_FN(unsigned long)

CCINFRA_NS_END

#endif
