#include "magellan/framework/core/TestCase.h"
#include "magellan/framework/core/TestFunctor.h"
#include "magellan/framework/core/TestResult.h"

MAGELLAN_NS_BEGIN

namespace
{
    struct TestFunctorWrapper : TestFunctor
    {
        using Method = void(TestCase::*)();
        
        TestFunctorWrapper(TestCase& target, Method method)
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
    return result.protect(*this, TestFunctorWrapper(*this, functor), desc);
}

#define PROTECT(action) protect(result, &TestCase::action, #action" failed")

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

const std::string& TestCase::getName() const
{
    return name;
}

MAGELLAN_NS_END
