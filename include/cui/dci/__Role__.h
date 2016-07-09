#ifndef HF8E7C28D_81E3_45AC_BF63_B1AFDB2E3FC3
#define HF8E7C28D_81E3_45AC_BF63_B1AFDB2E3FC3

#include <cui/base/__Keywords__.h>

#define __ROLE__(role) get##role()
#define __ROLE_PROTO_TYPE__(role) role& __ROLE__(role) const
#define __USE_ROLE__(role) virtual __ROLE_PROTO_TYPE__(role) = 0
#define __HAS_ROLE__(role) __USE_ROLE__(role)

//////////////////////////////////////////////////////////////////
#define __IMPL_ROLE__(role)                                       \
__ROLE_PROTO_TYPE__(role)                                         \
{                                                             \
   return const_cast<role&>(static_cast<const role&>(*this)); \
}

//////////////////////////////////////////////////////////////////////////
#define __DECL_ROLE__(role) __ROLE_PROTO_TYPE__(role)

//////////////////////////////////////////////////////////////////////////
#define __ROLE_CAST_TO__(role, obj)       \
    return const_cast<role&>(static_cast<const role&>(obj))

//////////////////////////////////////////////////////////////////////////
#define __IMPL_ROLE_WITH_OBJ__(role, obj)   \
    __DECL_ROLE__(role)  { __ROLE_CAST_TO__(role, obj); }

/////////////////////////////////////////////////////////////////////////////
namespace details
{
   template<typename T>
   struct Trait
   {
      virtual ~Trait() {}
   };
}

#define __TRAIT__(trait)  struct trait : ::details::Trait<trait>

#define __SELF__(self, trait) static_cast<trait&>(self)

#endif

