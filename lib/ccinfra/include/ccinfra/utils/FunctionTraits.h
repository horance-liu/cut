#ifndef H5E28F16B_BEA7_4E11_84A7_03E3D4C29B5A
#define H5E28F16B_BEA7_4E11_84A7_03E3D4C29B5A

#include <ccinfra/ccinfra.h>
#include <tuple>
#include <stddef.h>

CCINFRA_NS_BEGIN

template<typename T>
struct function_traits
: function_traits<decltype(&T::operator())>
{
};

template<typename ClassType, typename Arg>
struct function_traits<void (ClassType::*)(const Arg&) const>
{
    typedef Arg argument_type;
};

template<typename ClassType, typename Arg>
struct function_traits<void (ClassType::*)(Arg&) const>
{
    typedef Arg argument_type;
};

// XXX: below is the complete version!
template<typename ClassType, typename ReturnType, typename ... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
{
    enum {arity = sizeof ...(Args)};
    typedef ReturnType result_type;

    template<size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...> >::type type;
    };
};

#define ARG_TYPE(LAMDA) typename ::CCINFRA_NS::function_traits<LAMDA>::argument_type

CCINFRA_NS_END

#endif
