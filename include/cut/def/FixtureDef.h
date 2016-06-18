#ifndef HBAD0E026_1661_48E7_B0EE_F3DA07EA24F9
#define HBAD0E026_1661_48E7_B0EE_F3DA07EA24F9

#include <cub/utils/Symbol.h>
#include <cut/core/TestFixture.h>
#include <cut/auto/AutoTestSuite.h>

////////////////////////////////////////////////////////////////////////////////
#define DEF_FIXTURE(fixture, super)                                \
struct fixture;                                                    \
static cut::AutoTestSuite<fixture> UNIQUE_NAME(auto_suite_);  \
struct fixture : super

////////////////////////////////////////////////////////////////////////////////
#define FIXTURE(fixture)  DEF_FIXTURE(fixture, cut::TestFixture)

////////////////////////////////////////////////////////////////////////////////
#define SETUP()    OVERRIDE(void setUp())
#define TEARDOWN() OVERRIDE(void tearDown())

////////////////////////////////////////////////////////////////////////////////
#define SUPER_SETUP(super)    super::setUp()
#define SUPER_TEARDOWN(super) super::tearDown()

#endif
