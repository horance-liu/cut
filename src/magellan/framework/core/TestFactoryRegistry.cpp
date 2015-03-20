#include "magellan/framework/core/TestFactoryRegistry.h"
#include "magellan/framework/core/TestSuite.h"
#include <map>

MAGELLAN_NS_BEGIN

namespace
{
    struct TestFactoryRegistryRepository
    {
        static TestFactoryRegistryRepository& getInstance()
        {
            static TestFactoryRegistryRepository inst;
            return inst;
        }

        ~TestFactoryRegistryRepository()
        {
            for(auto entry : registries)
            {
                delete entry.second;
            }
        }
        
        TestFactoryRegistry& getRegistry(const std::string& name)
        {
            auto found = registries.find(name);
            if(found != registries.end())
            {
                return *found->second;
            }

            auto registry = new TestFactoryRegistry(name);
            registries[name] = registry;

            return *registry;
        }

    private:
        std::map<std::string, TestFactoryRegistry*> registries;
    };
}

TestFactoryRegistry& TestFactoryRegistry::getRegistry(const std::string& name)
{
    return TestFactoryRegistryRepository::getInstance().getRegistry(name);
}

TestFactoryRegistry::TestFactoryRegistry(const std::string& name)
    : name(name)
{
}

Test* TestFactoryRegistry::make()
{
    auto suite = new TestSuite(name);
    
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

void TestFactoryRegistry::addRegistry(const std::string& name)
{
    addFactory(getRegistry(name));
}

MAGELLAN_NS_END
