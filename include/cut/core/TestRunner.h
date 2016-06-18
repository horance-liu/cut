#ifndef H6DE28224_E43F_4689_BA39_491C30F80764
#define H6DE28224_E43F_4689_BA39_491C30F80764

#include <cut/cut.h>
#include <cub/dci/Role.h>

CUT_NS_BEGIN

struct Test;
struct TestResult;
struct TestListener;
struct TestOptions;
struct TestFactorySuite;

DEFINE_ROLE(TestRunner)
{
    bool run();

private:
    bool run(Test* test);
    void addListeners(TestResult& result) const;

    TestListener* makeXmlPrinter() const;

private:
    USE_ROLE(TestOptions);
    USE_ROLE(TestFactorySuite);
};

CUT_NS_END

#endif
