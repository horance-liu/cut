#ifndef _8CK6L6MV72FIARV2LMEHCKBEU497MCS5XDXSFOKXW38NULPPOO6OVC4P               
#define _8CK6L6MV72FIARV2LMEHCKBEU497MCS5XDXSFOKXW38NULPPOO6OVC4P

#include "magellan/core/TestFactory.h"
#include <set>

MAGELLAN_NS_BEGIN

struct TestSuite;

struct TestFactoryRegistry : TestFactory
{
    void addFactory(TestFactory&);

private:
    OVERRIDE(Test* make());

private:
   std::set<TestFactory*> factories;
};

MAGELLAN_NS_END

#endif
