#ifndef HF7E6F72A_F9D7_4EBE_8D80_4F69B82A5813
#define HF7E6F72A_F9D7_4EBE_8D80_4F69B82A5813

#include <cui/cui.h>
#include <cui/utils/__Symbol__.h>

CUI_NS_BEGIN

template <typename F>
struct ScopeExit
{
    ScopeExit(F f) : f(f)
    {}

    ~ScopeExit()
    { f(); }

private:
    F f;
};

template <typename F>
ScopeExit<F> make_scope_exit(F f)
{
    return ScopeExit<F>(f);
};

#define __SCOPE_EXIT__(code) \
    auto __UNIQUE_NAME__(scope_exit) = ::CUI_NS::make_scope_exit(code)

CUI_NS_END

#endif
