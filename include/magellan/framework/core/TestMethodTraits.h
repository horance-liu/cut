#ifndef H900A8CCD_FC94_4E1F_BA46_4CFA9D1A5B93
#define H900A8CCD_FC94_4E1F_BA46_4CFA9D1A5B93

#include <magellan/framework/core/MetaTestFixture.h>

MAGELLAN_NS_BEGIN

template <typename Fixture>
struct TestMethodTraits
{
    using Method = void (Fixture::*)();

    TestMethodTraits(int id, Method method, const std::string& name)
    {
        MetaTestFixture<Fixture>::registryMethod(id, method, name);
    }
};

MAGELLAN_NS_END

#endif
