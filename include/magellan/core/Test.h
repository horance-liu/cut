#ifndef _30KHGDCAF3MOKCBO9D1E7TLHUX8AUQ8FLRZ2MNXSJTX011I7KFOCMGJY               
#define _30KHGDCAF3MOKCBO9D1E7TLHUX8AUQ8FLRZ2MNXSJTX011I7KFOCMGJY

#include <magellan/base/magellan.h>
#include <infra/base/Role.h>
#include <string>

MAGELLAN_NS_BEGIN

struct TestResult;

DEFINE_ROLE(Test)
{
    ABSTRACT(void run(TestResult&));
    ABSTRACT(int countTestCases() const);
    ABSTRACT(const std::string& getName () const);
};

MAGELLAN_NS_END

#endif
