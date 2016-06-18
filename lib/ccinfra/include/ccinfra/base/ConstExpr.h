#ifndef HA506917F_7BD6_499B_AB91_F058FF6B64E5
#define HA506917F_7BD6_499B_AB91_F058FF6B64E5

#include <ccinfra/base/Config.h>

#if __SUPPORT_GENERAL_CONST_EXPR
# define CONST_EXPR  constexpr
#else
# define CONST_EXPR
#endif

#endif
