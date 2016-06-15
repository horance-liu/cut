#ifndef H850C3C7A_82E6_49C1_B47A_4BBB2F6EA3A3
#define H850C3C7A_82E6_49C1_B47A_4BBB2F6EA3A3

#include <ccinfra/utils/Symbol.h>
#include <magellan/auto/TestMethodTraits.h>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////
#define __TEST_NAME(id)     JOIN(test_, id)
#define __TEST_TRAITS(id)   JOIN(test_traits_, id)
#define __TEST_REGISTER(id) JOIN(register_test_, id)

////////////////////////////////////////////////////////////////////////////////
#define __DEF_TEST(id, name)                                          \
private:                                                              \
magellan::TestMethodTraits __TEST_REGISTER(id)()                      \
{                                                                     \
    using fixture_type = std::remove_pointer<decltype(this)>::type;   \
    auto test_case = &fixture_type::__TEST_NAME(id);                  \
    return magellan::TestMethodTraits(id, test_case, name);           \
}                                                                     \
magellan::TestMethodTraits __TEST_TRAITS(id) = __TEST_REGISTER(id)(); \
public:                                                               \
void __TEST_NAME(id)()

////////////////////////////////////////////////////////////////////////////////
#define TEST(name) __DEF_TEST(UNIQUE_ID, name)

#endif
