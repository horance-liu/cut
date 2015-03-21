#ifndef H8830446F_F68B_4ECB_945B_1474064EB768
#define H8830446F_F68B_4ECB_945B_1474064EB768

#include "magellan/framework/core/TestCase.h"

MAGELLAN_NS_BEGIN

template <typename Fixture>
struct TestCaller : TestCase
{
    using Method = void(Fixture::*)();

    TestCaller(const std::string& name, const Method method)
        : TestCase(name), method(method)
    {}

private:
    OVERRIDE(void setUp())
    {
        fixture = new Fixture;
        fixture->setUp();
    }

    OVERRIDE(void tearDown())
    {
        fixture->tearDown();
        delete fixture;
        fixture = nullptr;
    }

    OVERRIDE(void runTest())
    {
        (fixture->*method)();
    }

private:
    Fixture* fixture = nullptr;
    Method method = nullptr;
};

MAGELLAN_NS_END

#endif
