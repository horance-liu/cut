#ifndef H3175F5B7_3EBF_4468_AED7_8FF395B88AF7
#define H3175F5B7_3EBF_4468_AED7_8FF395B88AF7

#include "magellan/core/TestCaller.h"
#include "magellan/hook/runtime/Runtime.h"
#include "magellan/startup/TestOptions.h"
#include "ccinfra/base/TypeName.h"
#include <iostream>

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
        auto name = getFullName();
        return RUNTIME(TestOptions).filter(name) ?
            new TestCaller<Fixture>(name, method) : nullptr;
    }

    bool operator<(const TestMethod<Fixture>& rhs) const
    {
        return id < rhs.id;
    }

private:
    std::string getFullName() const
    {
        return ccinfra::TypeName<Fixture>::value() + "::" + name;
    }

private:
    int id;
    Method method;
    std::string name;
};

MAGELLAN_NS_END

#endif
