#include "magellan/listener/util/TestInfo.h"

MAGELLAN_NS_BEGIN

TestInfo::TestInfo()
    : timer(new Timer)
    , succ(true)
    , failure(false)
    , error(false)
{}

void TestInfo::onFailure()
{
   succ = false;
   failure = true;
}

void TestInfo::onError()
{
   succ = false;
   error = true;
}

bool TestInfo::isSucc() const
{
   return succ;
}

bool TestInfo::isFailure() const
{
   return !succ && failure;
}

bool TestInfo::isError() const
{
   return !succ && error;
}

timeval TestInfo::elapsedTime()
{
   return timer->getElapsedTime();
}

MAGELLAN_NS_END
