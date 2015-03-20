#ifndef H83B2114F_E03D_4F23_8451_F8A493731A77
#define H83B2114F_E03D_4F23_8451_F8A493731A77

namespace details
{
   template <typename T>
   struct DefaultValue
   {
      static T value() { return T(); }
   };

   template <typename T>
   struct DefaultValue<T*>
   {
       static T* value() { return nullptr; }
   };

   template <typename T>
   struct DefaultValue<const T*>
   {
       static T* value() { return nullptr; }
   };

   template <>
   struct DefaultValue<void>
   {
      static void value() {}
   };
}

#define DEFAULT(type, method)  \
    virtual type method { return ::details::DefaultValue<type>::value(); }

#endif
