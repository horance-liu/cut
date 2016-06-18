#ifndef _EM7NQ5392XET3HU9T1F55VEUXF7IF2VL9NRNSB7LM17OT1G8VM8P0TD               
#define _EM7NQ5392XET3HU9T1F55VEUXF7IF2VL9NRNSB7LM17OT1G8VM8P0TD

#include "magellan/core/TestMethod.h"
#include "magellan/core/TestSuite.h"
#include "cub/utils/TypeName.h"
#include <set>

MAGELLAN_NS_BEGIN

template <typename Fixture>
struct MetaTestFixture
{
    using Method = void(Fixture::*)();

    static void registryMethod(int id, Method method, const std::string& name)
    {
        methods().put(TestMethod<Fixture>(id, method, name));
    }

    static Test* suite()
    {
        return methods().suite();
    }

private:
    struct TestMethodRegistry
    {
        void put(const TestMethod<Fixture>& method)
        {
            if (registry.find(method) == registry.end())
            {
                registry.insert(method);
            }
        }

        Test* suite() const
        {
            auto fixture = new TestSuite(cub::TypeName<Fixture>::value());

            for (auto& method : registry)
            {
                fixture->addTest(method.makeTest());
            }

            return fixture;
        }

    private:
        std::set<TestMethod<Fixture>> registry;
    };

    static TestMethodRegistry& methods()
    {
        static TestMethodRegistry inst;
        return inst;
    }
};

MAGELLAN_NS_END

#endif
