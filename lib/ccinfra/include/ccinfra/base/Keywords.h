#ifndef H05B2224D_B926_4FC0_A936_97B52B8A98DB
#define H05B2224D_B926_4FC0_A936_97B52B8A98DB

#include <ccinfra/ccinfra.h>
#include <ccinfra/base/Default.h>
#include <ccinfra/base/Config.h>

CCINFRA_NS_BEGIN

namespace details
{
   template<typename T>
   struct Interface
   {
      virtual ~Interface() {}
   };
}

#define DEF_INTERFACE(Intf)  struct Intf : ::CCINFRA_NS::details::Interface<Intf>

#define ABSTRACT(...) virtual __VA_ARGS__ = 0

#if __SUPPORT_VIRTUAL_OVERRIDE
#   define OVERRIDE(...) virtual __VA_ARGS__ override
#else
#   define OVERRIDE(...) virtual __VA_ARGS__
#endif

#define EXTENDS(...) , ##__VA_ARGS__
#define IMPLEMENTS(...) EXTENDS(__VA_ARGS__)

CCINFRA_NS_END

#endif

