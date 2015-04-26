#include "magellan/auto/TestFactoryRegistry.h"
#include "magellan/core/TestSuite.h"

MAGELLAN_NS_BEGIN

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
