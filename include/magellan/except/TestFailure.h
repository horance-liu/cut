#ifndef H819CE325_EFE1_471E_B1A0_4E74D37465B6
#define H819CE325_EFE1_471E_B1A0_4E74D37465B6

#include "magellan/except/Message.h"

MAGELLAN_NS_BEGIN

struct Test;
struct TestFunctor;

struct TestFailure
{
    TestFailure(const TestFunctor& method, Message&& msg, bool failure);

    const std::string& getTestName() const;
    const std::string& getExceptionMsg() const;

    bool isFailure() const;

private:
    const Test &test;
    const Message msg;
    bool failure;
};

MAGELLAN_NS_END

#endif
