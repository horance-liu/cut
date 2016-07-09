#ifndef H1A60CE17_7D0C_4439_ACFD_C68C58302CA3
#define H1A60CE17_7D0C_4439_ACFD_C68C58302CA3

#include <cui/cui.h>

CUI_NS_BEGIN

namespace details
{
   template <typename T>
   struct DefaultValue
   {
      static T value()
      {
         return T();
      }
   };

   template <typename T>
   struct DefaultValue<T*>
   {
       static T* value()
       {
           return 0;
       }
   };

   template <typename T>
   struct DefaultValue<const T*>
   {
       static T* value()
       {
           return 0;
       }
   };

   template <>
   struct DefaultValue<void>
   {
      static void value()
      {
      }
   };
}

#define __DEFAULT__(type, method)  \
    virtual type method { return ::CUI_NS::details::DefaultValue<type>::value(); }

CUI_NS_END

#endif

