#ifndef H05B2224D_B926_4FC0_A936_97B52B8A99DB
#define H05B2224D_B926_4FC0_A936_97B52B8A99DB

#include <ccinfra/base/Config.h>

#if __SUPPORT_NULL_PTR
#define __null_ptr nullptr
#else
#define __null_ptr 0
#endif

#define __NOT_NULL(ptr) ptr != __null_ptr
#define __IS_NULL(ptr) ptr == __null_ptr

#endif

