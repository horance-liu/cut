#include <cui/utils/__TypeName__.h>

#if defined(__GNUC__)
#include <cxxabi.h>
#endif

#include <stdlib.h>

CUI_NS_BEGIN

std::string getDemangledName(const std::type_info& type)
{
#if defined(__GNUC__)
   int status = 0;

   char* name = abi::__cxa_demangle( type.name(), 0, 0, & status);

   std::string result(name);

   ::free(name);

   return result;
#else
   return typeInfo.name();
#endif
}

CUI_NS_END
