#ifndef HF13551D3_F3DC_472D_80CB_0CFECC0398F1
#define HF13551D3_F3DC_472D_80CB_0CFECC0398F1

#include <string>
#include <typeinfo>
#include <cui/cui.h>

CUI_NS_BEGIN

///////////////////////////////////////////////////////////////
std::string getDemangledName(const std::type_info& typeInfo);

///////////////////////////////////////////////////////////////
template<typename T>
struct TypeName
{
    static std::string value()
    {
        return getDemangledName(typeid(T));
    }
};

///////////////////////////////////////////////////////////////
template<>
struct TypeName<std::string>
{
    static std::string value() { return "std::string"; }
};

///////////////////////////////////////////////////////////////
template<>
struct TypeName<std::nullptr_t>
{
    static std::string value() { return "std::nullptr_t"; }
};

CUI_NS_END

#endif
