#include "magellan/framework/auto/TestFactoryRegistry.h"
#include "magellan/framework/core/TestSuite.h"

MAGELLAN_NS_BEGIN

TestFactoryRegistry& TestFactoryRegistry::getInstance()
{
    static TestFactoryRegistry registry;
    return registry;
}

Test* TestFactoryRegistry::make()
{
    auto suite = new TestSuite("All Tests");
    
    for (auto factory : factories)
    {
        suite->addTest(factory->make()); 
    }
    
    return suite;
}

void TestFactoryRegistry::addFactory(TestFactory& factory)
{
    factories.insert(&factory);
}

MAGELLAN_NS_END
