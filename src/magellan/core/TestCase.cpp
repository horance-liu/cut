#include <magellan/core/TestCase.h>
#include <magellan/core/TestResult.h>
#include <magellan/core/TestFunctor.h>

MAGELLAN_NS_BEGIN

namespace
{
    struct TestCaseMethodFunctor : TestFunctor
    {
        using TestCaseMethod = void(TestCase::*)();
        using ConstTestCaseMethod = void(TestCase::*)() const;
        
        TestCaseMethodFunctor(const TestCase& target, TestCaseMethod method)
            : target(const_cast<TestCase&>(target))
            , method(method)
        {
        }

        TestCaseMethodFunctor(const TestCase& target, const ConstTestCaseMethod method)
          : TestCaseMethodFunctor(target, (TestCaseMethod)method)
        {
        }

    private:
        OVERRIDE(bool operator()() const)
        {
            (target.*method)();
            return true;
        }

    private:
       TestCase& target;
       TestCaseMethod method;
    };
}

TestCase::TestCase(const std::string& name) : name(name)
{
}

template <typename Functor>
inline bool TestCase::protect(TestResult& result, Functor functor, const char* desc) const
{
    return result.protect(TestCaseMethodFunctor(*this, functor), *this, desc);
}

inline void TestCase::doRun(TestResult& result) const
{
    if (protect(result, &TestCase::setUp, "setUp() failed"))
    {
        protect(result, &TestCase::runTest);
    }

    protect(result, &TestCase::tearDown, "tearDown() failed");
}

void TestCase::run(TestResult& result) const
{
    result.startTest(*this);
    doRun(result);
    result.endTest(*this);
}

int TestCase::getNumOfTestCases() const
{
    return 1;
}

const std::string& TestCase::getName() const
{
    return name;
}

MAGELLAN_NS_END

