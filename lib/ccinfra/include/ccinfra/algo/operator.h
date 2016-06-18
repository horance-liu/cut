#ifndef HE6A8C65F_5BCB_4E25_AF7B_5F438718A56C
#define HE6A8C65F_5BCB_4E25_AF7B_5F438718A56C

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
