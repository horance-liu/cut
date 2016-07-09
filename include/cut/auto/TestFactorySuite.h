#ifndef _8CK6L6MV72FIARV2LMEHCKBEU497MCS5XDXSFOKXW38NULPPOO6OVC4P               
#define _8CK6L6MV72FIARV2LMEHCKBEU497MCS5XDXSFOKXW38NULPPOO6OVC4P

#include <cut/core/TestFactory.h>
#include <set>

CUT_NS_BEGIN

struct TestSuite;

struct TestFactorySuite : TestFactory
{
    void addFactory(TestFactory&);

private:
    __OVERRIDE__(Test* make());

private:
   std::set<TestFactory*> factories;
};

CUT_NS_END

#endif
