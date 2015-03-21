#ifndef HBAD0E026_1661_48E7_B0EE_F3DA07EA24F9
#define HBAD0E026_1661_48E7_B0EE_F3DA07EA24F9

#include <magellan/infra/std/Symbol.h>
#include <magellan/framework/core/TestFixture.h>
#include <magellan/framework/auto/AutoTestSuite.h>
#include <magellan/framework/traits/FixtureTraits.h>

////////////////////////////////////////////////////////////////////////////////
#define __DEF_FIXTURE(fixture)                                     \
struct fixture;                                                    \
static magellan::AutoTestSuite<fixture> UNIQUE_NAME(auto_suite_);  \
struct fixture : magellan::TestFixture, magellan::FixtureTraits<fixture>

////////////////////////////////////////////////////////////////////////////////
#define FIXTURE(fixture)  __DEF_FIXTURE(fixture##Test)

////////////////////////////////////////////////////////////////////////////////
#define SETUP()    OVERRIDE(void setUp())
#define TEARDOWN() OVERRIDE(void tearDown())

#endif
