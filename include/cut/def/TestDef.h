#ifndef H850C3C7A_82E6_49C1_B47A_4BBB2F6EA3A3
#define H850C3C7A_82E6_49C1_B47A_4BBB2F6EA3A3

#include <cui/utils/__Symbol__.h>
#include <cut/auto/TestMethodTraits.h>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////
#define __TEST_NAME(id)     __JOIN__(test_, id)
#define __TEST___TRAIT__S(id)   __JOIN__(test_traits_, id)
#define __TEST_REGISTER(id) __JOIN__(register_test_, id)

////////////////////////////////////////////////////////////////////////////////
#define __DEF_TEST(id, name)                                          \
private:                                                              \
cut::TestMethodTraits __TEST_REGISTER(id)()                      \
{                                                                     \
    using fixture_type = std::remove_pointer<decltype(this)>::type;   \
    auto test_case = &fixture_type::__TEST_NAME(id);                  \
    return cut::TestMethodTraits(id, test_case, name);           \
}                                                                     \
cut::TestMethodTraits __TEST___TRAIT__S(id) = __TEST_REGISTER(id)(); \
public:                                                               \
void __TEST_NAME(id)()

////////////////////////////////////////////////////////////////////////////////
#define TEST(name) __DEF_TEST(__UNIQUE_ID__, name)

#endif
