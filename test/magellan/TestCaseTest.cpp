#include <cut/cut.hpp>
#include <cut/core/TestResult.h>
#include <cut/core/TestListener.h>
#include <cut/except/TestFailure.h>
#include <functional>
#include <exception>
#include <new>

USING_CUT_NS
USING_HAMCREST_NS

namespace
{
    struct FakeTestCase : TestCase
    {
        FakeTestCase(std::function<void()> functor)
          : TestCase("FakeTestCase::Functor")
          , functor(functor)
        {}

    private:
        OVERRIDE(void runTest())
        {
            functor();
        }

    private:
        std::function<void()> functor;
    };

    struct FakeTestResultCollector : TestListener
    {
        OVERRIDE(void addFailure(const TestFailure& failure))
        {
            numOfFail++;
            failure.isFailure() ? numOfFailure++ : numOfError++;
        }

        int numOfFail = 0;
        int numOfFailure = 0;
        int numOfError = 0;
    };
}

FIXTURE(TestCaseTest)
{
    FakeTestResultCollector* collector = new FakeTestResultCollector;
    TestResult result;

    TestCaseTest()
    {
        result.add(collector);
    }

    template <typename Functor>
    void run_test(Functor f)
    {
        FakeTestCase(f).runBare(result);
    }

    TEST("when test case assert success")
    {
        run_test([] { ASSERT_THAT(1, is(1)); });
        ASSERT_THAT(collector->numOfFail, is(0));
    }

    TEST("when test case assert fail")
    {
        run_test([] { ASSERT_THAT(1, is(2)); });
        ASSERT_THAT(collector->numOfFail, is(1));
        ASSERT_THAT(collector->numOfFailure, is(1));
    }

    TEST("when test case throw std::exception")
    {
        run_test([] { throw std::exception(); });
        ASSERT_THAT(collector->numOfFail, is(1));
        ASSERT_THAT(collector->numOfError, is(1));
    }

    TEST("when test case throw std::bad_alloc")
    {
        run_test([] { throw std::bad_alloc(); });
        ASSERT_THAT(collector->numOfFail, is(1));
        ASSERT_THAT(collector->numOfError, is(1));
    }
};
