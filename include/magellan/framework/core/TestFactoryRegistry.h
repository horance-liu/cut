#ifndef _8CK6L6MV72FIARV2LMEHCKBEU497MCS5XDXSFOKXW38NULPPOO6OVC4P               
#define _8CK6L6MV72FIARV2LMEHCKBEU497MCS5XDXSFOKXW38NULPPOO6OVC4P

#include <string>
#include <set>
#include "magellan/framework/core/TestFactory.h"

MAGELLAN_NS_BEGIN

struct TestSuite;

struct TestFactoryRegistry : TestFactory
{
    explicit TestFactoryRegistry(const std::string& name);

    void addFactory(TestFactory&);
    void addRegistry(const std::string& name);

    static TestFactoryRegistry& getRegistry(const std::string& name = "All Tests");

private:
    OVERRIDE(Test* make());

private:
    const std::string name;
    std::set<TestFactory*> factories;
};

MAGELLAN_NS_END

#endif
