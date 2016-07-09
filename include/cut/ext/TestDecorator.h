#ifndef H62CE7126_24F8_4A34_B0D6_DD977DA838B7
#define H62CE7126_24F8_4A34_B0D6_DD977DA838B7

#include <cut/core/Test.h>

CUT_NS_BEGIN

struct TestDecorator : Test
{
    explicit TestDecorator(Test& test);

protected:
    __OVERRIDE__(void run(TestResult&));
    __OVERRIDE__(int countTestCases() const);
    __OVERRIDE__(int countChildTests() const);
    __OVERRIDE__(const std::string& getName () const);

private:
    Test& test;
};

CUT_NS_END

#endif
