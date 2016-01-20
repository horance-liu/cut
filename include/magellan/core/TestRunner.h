#ifndef H6DE28224_E43F_4689_BA39_491C30F80764
#define H6DE28224_E43F_4689_BA39_491C30F80764

#include "magellan/magellan.h"
#include "l0-infra/dci/Role.h"

MAGELLAN_NS_BEGIN

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

MAGELLAN_NS_END

#endif
