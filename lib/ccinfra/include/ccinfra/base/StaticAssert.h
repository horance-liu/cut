#ifndef H671141B2_B247_540B_8E83_476558110FFE
#define H671141B2_B247_540B_8E83_476558110FFE

#include <ccinfra/base/Config.h>

#if __SUPPORT_STATIC_ASSERT
# define STATIC_ASSERT(expr) static_assert(expr, #expr)
#else
# define STATIC_ASSERT(expr) do {               \
    enum { static_assert_failure = 1/(expr) };  \
} while(0)
#endif

#endif
