#ifndef MAMSDLFKE_UIETUOM_3746_JFOIEWNNVJ_38457_NVHDYW
#define MAMSDLFKE_UIETUOM_3746_JFOIEWNNVJ_38457_NVHDYW

#include <string>
#include <typeinfo>

///////////////////////////////////////////////////////////////
std::string getDemangledName(const std::type_info& typeInfo);

///////////////////////////////////////////////////////////////
template<typename T>
struct TypeString
{
    static std::string value()
    {
        return getDemangledName(typeid(T));
    }
};

///////////////////////////////////////////////////////////////
template<>
struct TypeString<std::string>
{
    static std::string value() { return "std::string"; }
};

#endif

