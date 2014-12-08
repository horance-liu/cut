#ifndef H8830446F_F68B_4ECB_945B_1474064EB768
#define H8830446F_F68B_4ECB_945B_1474064EB768

#include <magellan/core/TestCase.h>

MAGELLAN_NS_BEGIN

template <typename Fixture>
struct TestCaller : TestCase
{
    using Method = void(Fixture::*)();

    TestCaller(const std::string& name, const Method method)
        : TestCase(name), fixture(nullptr), method(method)
    {
    }

private:
    OVERRIDE(void setUp())
    {
        // must not register test method to MetaTestFixture again.
        fixture = new Fixture;
        fixture->setUp();
    }

    OVERRIDE(void tearDown())
    {
        delete fixture;
        fixture = nullptr;
    }

    OVERRIDE(void runTest())
    {
        (fixture->*method)();
    }

private:
    Fixture* fixture;
    Method method;
};

MAGELLAN_NS_END

#endif
