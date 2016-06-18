#ifndef _30KHGDCAF3MOKCBO9D1E7TLHUX8AUQ8FLRZ2MNXSJTX011I7KFOCMGJY               
#define _30KHGDCAF3MOKCBO9D1E7TLHUX8AUQ8FLRZ2MNXSJTX011I7KFOCMGJY

#include <cut/cut.h>
#include <cub/dci/Role.h>
#include <string>

CUT_NS_BEGIN

struct TestResult;

DEFINE_ROLE(Test)
{
    ABSTRACT(const std::string& getName () const);
    ABSTRACT(int countTestCases() const);
    ABSTRACT(int countChildTests() const);
    ABSTRACT(void run(TestResult&));
};

CUT_NS_END

#endif
