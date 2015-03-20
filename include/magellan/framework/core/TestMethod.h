#ifndef H3175F5B7_3EBF_4468_AED7_8FF395B88AF7
#define H3175F5B7_3EBF_4468_AED7_8FF395B88AF7

#include "magellan/framework/core/TestCaller.h"

MAGELLAN_NS_BEGIN

template <typename Fixture>
struct TestMethod
{
    using Method = void(Fixture::*)();

    TestMethod(const std::string& name, const Method method)
        : name(name), method(method)
    {
    }

    Test* makeTest()
    {
        return new TestCaller<Fixture>(name, method);
    }

private:
    std::string name;
    Method method;
};

MAGELLAN_NS_END

#endif
