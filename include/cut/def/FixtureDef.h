#ifndef HBAD0E026_1661_48E7_B0EE_F3DA07EA24F9
#define HBAD0E026_1661_48E7_B0EE_F3DA07EA24F9

#include <cui/utils/__Symbol__.h>
#include <cut/core/TestFixture.h>
#include <cut/auto/AutoTestSuite.h>

////////////////////////////////////////////////////////////////////////////////
#define DEF_FIXTURE(fixture, super)                                \
struct fixture;                                                    \
static cut::AutoTestSuite<fixture> __UNIQUE_NAME__(auto_suite);  \
struct fixture : super

////////////////////////////////////////////////////////////////////////////////
#define FIXTURE(fixture)  DEF_FIXTURE(fixture, cut::TestFixture)

////////////////////////////////////////////////////////////////////////////////
#define SETUP()    __OVERRIDE__(void setUp())
#define TEARDOWN() __OVERRIDE__(void tearDown())

////////////////////////////////////////////////////////////////////////////////
#define SUPER_SETUP(super)    super::setUp()
#define SUPER_TEARDOWN(super) super::tearDown()

#endif
