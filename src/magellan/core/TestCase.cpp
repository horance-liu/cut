#include <magellan/core/TestCase.h>
#include <magellan/core/TestResult.h>
#include "magellan/core/TestMethod.h"

MAGELLAN_NS_BEGIN

namespace
{
    struct TestMethodWrapper : TestMethod
    {
        using Method = void(TestCase::*)();
        
        TestMethodWrapper(TestCase& target, Method method)
            : target(target), method(method)
        {}

    private:
        OVERRIDE(bool operator()() const)
        {
            (target.*method)();
            return true;
        }

    private:
       TestCase& target;
       Method method;
    };
}

TestCase::TestCase(const std::string& name) : name(name)
{
}

template <typename Functor>
inline bool TestCase::protect(TestResult& result, Functor functor, const char* desc)
{
    return result.protect(*this, TestMethodWrapper(*this, functor), desc);
}

void TestCase::runBare(TestResult& result)
{
#define PROTECT(action) protect(result, &TestCase::action, #action" failed")

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

const std::string& TestCase::getName() const
{
    return name;
}

MAGELLAN_NS_END
