#ifndef _YILL50M2RW1ONKOTDE31GYE4PZNVDLHH1CKFXS75LL4DA2NDCQSX9H5Y               
#define _YILL50M2RW1ONKOTDE31GYE4PZNVDLHH1CKFXS75LL4DA2NDCQSX9H5Y

#include <cut/core/Test.h>
#include <cut/core/TestFixture.h>

CUT_NS_BEGIN

struct TestCase : Test, TestFixture
{
    TestCase(const std::string& name);

    void runBare(TestResult&);

private:
    OVERRIDE(void run(TestResult&));
    OVERRIDE(int countTestCases() const);
    OVERRIDE(int countChildTests() const);
    OVERRIDE(const std::string& getName() const);

private:
    DEFAULT(void, runTest());

private:
    template <typename Functor>
    bool protect(TestResult& result, Functor functor, const char* desc = "");

private:
    const std::string name;
};

CUT_NS_END

#endif

