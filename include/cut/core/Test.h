#ifndef _30KHGDCAF3MOKCBO9D1E7TLHUX8AUQ8FLRZ2MNXSJTX011I7KFOCMGJY               
#define _30KHGDCAF3MOKCBO9D1E7TLHUX8AUQ8FLRZ2MNXSJTX011I7KFOCMGJY

#include <cui/dci/__Role__.h>
#include <cut/cut.h>
#include <string>

CUT_NS_BEGIN

struct TestResult;

__TRAIT__(Test)
{
    __ABSTRACT__(const std::string& getName () const);
    __ABSTRACT__(int countTestCases() const);
    __ABSTRACT__(int countChildTests() const);
    __ABSTRACT__(void run(TestResult&));
};

CUT_NS_END

#endif
