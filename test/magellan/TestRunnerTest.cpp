//#include "magellan/magellan.hpp"
//#include "magellan/core/TestRunner.h"
//#include "magellan/core/TestCase.h"
//#include "magellan/core/TestListener.h"
//#include "magellan/except/TestFailure.h"
//#include "magellan/core/TestResult.h"
//#include <functional>
//
//USING_MAGELLAN_NS
//USING_HAMCREST_NS
//
//namespace
//{
//    struct FakeTestCase : TestCase
//    {
//        FakeTestCase(const std::string& fixture, const std::string& name)
//            : TestCase(fixture, name)
//        {
//        }
//
//        FakeTestCase& setFunction(std::function<void()> functor)
//        {
//            this->functor = functor;
//
//            return *this;
//        }
//    private:
//        OVERRIDE(void runTest())
//        {
//            functor();
//        }
//
//    private:
//        std::function<void()> functor;
//    };
//
//    struct FakeTestResultCollector : TestListener
//    {
//        FakeTestResultCollector()
//            : numOfRunnedTestCase(0)
//            , numOfPassed(0)
//            , numOfFailure(0)
//        {
//
//        }
//
//        OVERRIDE(void startTest(const Test& test))
//        {
//            std::cout <<"Test Name:" <<test.getName();
//            numOfRunnedTestCase++;
//            numOfPassed++;
//        }
//
//        OVERRIDE(void addFailure(const TestFailure& failure))
//        {
//            if(failure.isFailure())
//            {
//                numOfFailure++;
//                numOfPassed--;
//            }
//        }
//
//        int numOfRunnedTestCase;
//        int numOfPassed;
//        int numOfFailure;
//    };
//}
//
//FIXTURE(TestRunnerTest)
//{
//    FakeTestResultCollector* collector = new FakeTestResultCollector;
//    TestResult result;
//
//    TestRunnerTest()
//    {
//        result.add(collector);
//    }
//
//    template <typename Functor>
//    void run_test(Functor f)
//    {
//        FakeTestCase testCase("filterTest", "set filter to magellan");
//        testCase.setFunction(f).runBare(result);
//    }
//
//    static const char** to_argv(std::vector<const char*>&& options)
//    {
//        const char** argv = new const char*[options.size()];
//
//        for (auto i = 0; i < options.size(); i++)
//        {
//            argv[i] = options[i];
//        }
//
//        return argv;
//    }
//
//
//   TEST("filter test for magellan")
//   {
//       TestRunner testRunner(1, to_argv({"--filter=set filter to magellan"}));
//       run_test([] { ASSERT_THAT(1, is(1)); });
//       ASSERT_THAT(collector->numOfRunnedTestCase, is(1));
//   }
//};
