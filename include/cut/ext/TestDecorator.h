#ifndef H62CE7126_24F8_4A34_B0D6_DD977DA838B7
#define H62CE7126_24F8_4A34_B0D6_DD977DA838B7

#include <cut/core/Test.h>

CUT_NS_BEGIN

struct TestDecorator : Test
{
    explicit TestDecorator(Test& test);

protected:
    OVERRIDE(void run(TestResult&));
    OVERRIDE(int countTestCases() const);
    OVERRIDE(int countChildTests() const);
    OVERRIDE(const std::string& getName () const);

private:
    Test& test;
};

CUT_NS_END

#endif
