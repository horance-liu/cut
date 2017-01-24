#include <cut/listener/util/TestInfo.h>

CUT_NS_BEGIN

TestInfo::TestInfo()
    : succ(true)
    , failure(false)
    , error(false)
    , timer(new Timer)
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

CUT_NS_END
