#ifndef TESTINFO1529C5B_742D_4014_B32D_7533B3DF905
#define TESTINFO1529C5B_742D_4014_B32D_7533B3DF905

#include "magellan/listener/util/Timer.h"
#include <memory>

MAGELLAN_NS_BEGIN

struct TestInfo
{
    TestInfo();

    void onFailure();
    void onError();
    bool isSucc() const;
    bool isFailure() const;
    bool isError() const;
    timeval elapsedTime();

private:
    bool succ;
    bool failure;
    bool error;
    std::unique_ptr<Timer> timer;
};

MAGELLAN_NS_END

#endif
