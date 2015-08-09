#include "magellan/core/TestCase.h"
#include "magellan/core/TestFunctor.h"
#include "magellan/core/TestResult.h"
#include "magellan/hook/runtime/Runtime.h"
#include "magellan/startup/TestOptions.h"

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

namespace
{
    bool isFilter(const std::string& name)
    {
        RUNTIME(TestOptions, options);
        return options.doFilter(name);
    }
}

void TestCase::run(TestResult& result)
{
    if(isFilter(name)) return;
    result.run(*this);
}

int TestCase::countTestCases() const
{
	return isFilter(name) ? 0 : 1;
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
