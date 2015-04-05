#ifndef _EM7NQ5392XET3HU9T1F55VEUXF7IF2VL9NRNSB7LM17OT1G8VM8P0TD               
#define _EM7NQ5392XET3HU9T1F55VEUXF7IF2VL9NRNSB7LM17OT1G8VM8P0TD

#include "magellan/core/TestMethod.h"
#include "magellan/core/TestSuite.h"
#include "l0-infra/std/TypeName.h"
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
        void put(TestMethod<Fixture>&& method)
        {
            if (registry.find(method) == registry.end())
            {
                registry.emplace(method);
            }
        }

        Test* suite() const
        {
            auto* result = new TestSuite(stdext::TypeName<Fixture>::value());

            for (auto& method : registry)
            {
                result->addTest(method.makeTest());
            }

            return result;
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
