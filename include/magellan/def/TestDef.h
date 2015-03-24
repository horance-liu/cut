#ifndef H850C3C7A_82E6_49C1_B47A_4BBB2F6EA3A3
#define H850C3C7A_82E6_49C1_B47A_4BBB2F6EA3A3

#include <l0-infra/std/Symbol.h>
#include <magellan/auto/TestMethodTraits.h>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////
#define TEST_NAME(id) JOIN(test_, id)

////////////////////////////////////////////////////////////////////////////////
#define __DEF_TEST(id, name) magellan::TestMethodTraits JOIN(test_traits_, id) \
{ id, &std::remove_pointer_t<decltype(this)>::TEST_NAME(id), name};            \
void TEST_NAME(id)()

////////////////////////////////////////////////////////////////////////////////
#define TEST(name) __DEF_TEST(UNIQUE_ID, name)

#endif
