#include <cut/auto/TestFactorySuite.h>
#include <cut/core/TestSuite.h>

CUT_NS_BEGIN

Test* TestFactorySuite::make()
{
    auto suite = new TestSuite("All Tests");
    
    for (auto factory : factories)
    {
        suite->addTest(factory->make()); 
    }
    
    return suite;
}

void TestFactorySuite::addFactory(TestFactory& factory)
{
    factories.insert(&factory);
}

CUT_NS_END
