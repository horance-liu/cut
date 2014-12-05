#ifndef H8830446F_F68B_4ECB_945B_1474064EB768
#define H8830446F_F68B_4ECB_945B_1474064EB768

#include <magellan/core/TestCase.h>

MAGELLAN_NS_BEGIN

template <typename Fixture>
struct TestCaller : TestCase
{
    using TestMethod = void (Fixture::*)() const;

    TestCaller(const std::string& name, TestMethod method)
        : TestCase(name), fixture(0), method(method)
    {
    }

private:
    OVERRIDE(void setUp())
    {
        fixture = new Fixture;
        fixture->setUp();
    }

    OVERRIDE(void tearDown())
    {
        delete fixture;
        fixture = 0;
    }

    OVERRIDE(void runTest())
    {
        (fixture->*method)();
    }

private:
    Fixture* fixture;
    TestMethod method;
};

MAGELLAN_NS_END

#endif

