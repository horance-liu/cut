#ifndef H819CE325_EFE1_471E_B1A0_4E74D37465B6
#define H819CE325_EFE1_471E_B1A0_4E74D37465B6

#include "magellan/framework/except/Message.h"

MAGELLAN_NS_BEGIN

struct Test;

struct TestFailure
{
    TestFailure(Test& test, const Message& msg, bool isError);

    bool isError() const;

private:
    Test &test;
    Message msg;
    bool error;
};

MAGELLAN_NS_END

#endif
