#ifndef H819CE325_EFE1_471E_B1A0_4E74D37465B6
#define H819CE325_EFE1_471E_B1A0_4E74D37465B6

#include "magellan/framework/except/Message.h"

MAGELLAN_NS_BEGIN

struct Test;

struct TestFailure
{
    TestFailure(const Test& test, const Message& msg, bool failture);

    const std::string& getTestName() const;
    std::string getExceptionMsg() const;
    bool isFailure() const;

private:
    const Test &test;
    const Message msg;
    const bool failture;
};

MAGELLAN_NS_END

#endif
