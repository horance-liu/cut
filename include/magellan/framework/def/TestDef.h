#ifndef H850C3C7A_82E6_49C1_B47A_4BBB2F6EA3A3
#define H850C3C7A_82E6_49C1_B47A_4BBB2F6EA3A3

#include <magellan/framework/core/TestMethodTraits.h>
#include <magellan/infra/std/Symbol.h>

////////////////////////////////////////////////////////////////////////////////
#define TEST_NAME(unique_id) JOIN(test_, unique_id)

////////////////////////////////////////////////////////////////////////////////
#define __DEF_TEST(id, name) magellan::TestMethodTraits<fixture_type> \
JOIN(test_traits_, id) { id, &fixture_type::TEST_NAME(id), name};     \
void TEST_NAME(id)()

////////////////////////////////////////////////////////////////////////////////
#define TEST(name) __DEF_TEST(__COUNTER__, name)

#endif
