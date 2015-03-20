#ifndef _EM7NQ5392XET3HU9T1F55VEUXF7IF2VL9NRNSB7LM17OT1G8VM8P0TD               
#define _EM7NQ5392XET3HU9T1F55VEUXF7IF2VL9NRNSB7LM17OT1G8VM8P0TD

#include <vector>
#include "magellan/framework/core/TestMethod.h"
#include "magellan/framework/core//TestSuite.h"

MAGELLAN_NS_BEGIN

template <typename Fixture>
class MetaTestFixture
{
    using Method = void(Fixture::*)();

    static void registryMethod(const std::string& name, const Method method)
    {
        getRegistry().emplace_back(name, method);
    }

    static Test* suite()
    {
        auto result = new TestSuite(Fixture::name);

        for (auto method : getRegistry())
        {
            result->addTest(method.makeTest());
        }

        return result;
    }

private:
    using TestMethodRegistry = std::vector<TestMethod<Fixture>>;

    static TestMethodRegistry& getRegistry()
    {
        static TestMethodRegistry registry;
        return registry;
    }
};

MAGELLAN_NS_END

#endif
