#ifndef H65EC9297_BAF2_449A_B266_88162B252586
#define H65EC9297_BAF2_449A_B266_88162B252586

#include <functional>
#include <string.h>

namespace std
{
    template <>
    struct equal_to<const char*> : binary_function<const char*, const char*, bool>
    {
        bool operator()(const char* const& x, const char* const& y) const
        { return strcmp(x, y) == 0; }
    };

    template <>
    struct not_equal_to<const char*> : binary_function<const char*, const char*, bool>
    {
        bool operator()(const char* const& x, const char* const& y) const
        { return strcmp(x, y) != 0; }
    };

    template <>
    struct less<const char*> : binary_function<const char*, const char*, bool>
    {
        bool operator()(const char* const& x, const char* const& y) const
        { return strcmp(x, y) < 0; }
    };

    template <>
    struct less_equal<const char*> : binary_function<const char*, const char*, bool>
    {
        bool operator()(const char* const& x, const char* const& y) const
        { return strcmp(x, y) <= 0; }
    };

    template <>
    struct greater<const char*> : binary_function<const char*, const char*, bool>
    {
        bool operator()(const char* const& x, const char* const& y) const
        { return strcmp(x, y) > 0; }
    };

    template <>
    struct greater_equal<const char*> : binary_function<const char*, const char*, bool>
    {
        bool operator()(const char* const& x, const char* const& y) const
        { return strcmp(x, y) >= 0; }
    };
}

#endif
