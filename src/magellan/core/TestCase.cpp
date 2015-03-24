#include "magellan/core/TestCase.h"
#include "magellan/core/TestFunctor.h"
#include "magellan/core/TestResult.h"

MAGELLAN_NS_BEGIN

TestCase::TestCase(const std::string& fixture, const std::string& name)
  : name(fixture + "::" + name)
{}

namespace
{
    struct TestCaseFunctor : TestFunctor
    {
        using Method = void(TestCase::*)();
        
        TestCaseFunctor(TestCase& test, Method method)
            : test(test), method(method)
        {}

    private:
        OVERRIDE(bool operator()() const)
        {
            (test.*method)();
            return true;
        }

        IMPL_ROLE_WITH_OBJ(Test, test);

    private:
       TestCase& test;
       Method method;
    };
}

template <typename Functor>
inline bool TestCase::protect(TestResult& result, Functor functor, const char* desc)
{
    return result.protect(TestCaseFunctor(*this, functor), desc);
}

#define PROTECT(functor) protect(result, &TestCase::functor, " in the "#functor)

void TestCase::runBare(TestResult& result)
{
    if (PROTECT(setUp))
    {
        PROTECT(runTest);
    }

    PROTECT(tearDown);
}

void TestCase::run(TestResult& result)
{
    result.run(*this);
}

int TestCase::countTestCases() const
{
    return 1;
}

int TestCase::countChildTests() const
{
    return 0;
}

const std::string& TestCase::getName() const
{
    return name;
}

MAGELLAN_NS_END
