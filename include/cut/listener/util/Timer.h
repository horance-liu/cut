#ifndef H7A073A3C_FC4D_42F8_B475_A0B118EC4B32
#define H7A073A3C_FC4D_42F8_B475_A0B118EC4B32

#include <cut/cut.h>

#if !defined(_MSC_VER)
#include <sys/time.h>
#endif

#if defined(_MSC_VER)
struct timeval
{
    unsigned int tv_sec;
    unsigned int tv_usec;
};
#endif

CUT_NS_BEGIN

struct Timer
{
    Timer();

    timeval getElapsedTime() const;

private:
    timeval startTime;
};

CUT_NS_END

#endif
