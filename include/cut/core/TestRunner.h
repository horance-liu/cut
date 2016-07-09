#ifndef H6DE28224_E43F_4689_BA39_491C30F80764
#define H6DE28224_E43F_4689_BA39_491C30F80764

#include <cui/dci/__Role__.h>
#include <cut/cut.h>

CUT_NS_BEGIN

struct Test;
struct TestResult;
struct TestListener;
struct TestOptions;
struct TestFactorySuite;

__TRAIT__(TestRunner)
{
    bool run();

private:
    bool run(Test* test);
    void addListeners(TestResult& result) const;

    TestListener* makeXmlPrinter() const;

private:
    __USE_ROLE__(TestOptions);
    __USE_ROLE__(TestFactorySuite);
};

CUT_NS_END

#endif
