#include <cut/core/TestCase.h>
#include <cut/core/TestFunctor.h>
#include <cut/core/TestResult.h>

CUT_NS_BEGIN

TestCase::TestCase(const std::string& name) : name(name)
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
        __OVERRIDE__(bool operator()() const)
        {
            (test.*method)();
            return true;
        }

        __IMPL_ROLE_WITH_OBJ__(Test, test);

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

CUT_NS_END
