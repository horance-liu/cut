#ifndef H3175F5B7_3EBF_4468_AED7_8FF395B88AF7
#define H3175F5B7_3EBF_4468_AED7_8FF395B88AF7

#include "magellan/framework/core/TestCaller.h"

MAGELLAN_NS_BEGIN

template <typename Fixture>
struct TestMethod
{
    using Method = void(Fixture::*)();

    TestMethod(int id, Method method, const std::string& name)
        : id(id), method(method), name(name)
    {}

    Test* makeTest() const
    {
        return new TestCaller<Fixture>(name, method);
    }

    bool operator<(const TestMethod<Fixture>& rhs) const
    {
        return id < rhs.id;
    }

private:
    int id;
    Method method;
    std::string name;
};

MAGELLAN_NS_END

#endif
