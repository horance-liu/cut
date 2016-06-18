#include <cut/listener/util/Timer.h>

#if defined(_MSC_VER)
#include <windows.h>
#endif

CUT_NS_BEGIN

////////////////////////////////////////////////////
namespace
{
#if defined(_MSC_VER)
    int gettimeofday(struct timeval* tv, void*)
    {
        union
        {
            long long ns100;
            FILETIME ft;
        }now;

        ::GetSystemTimeAsFileTime (&now.ft);
        tv->tv_usec = (long) ((now.ns100 / 10LL) % 1000000LL);
        tv->tv_sec = (long) ((now.ns100 - 116444736000000000LL) / 10000000LL);
        return (0);
    }
#endif

   timeval subtime(const timeval& end, const timeval& start)
   {
      timeval tv = end;
      while (tv.tv_usec < start.tv_usec)
      {
         tv.tv_usec += 1000000;
         tv.tv_sec--;
      }

      tv.tv_usec -= start.tv_usec;
      tv.tv_sec  -= start.tv_sec;

      return tv;
   }
}

Timer::Timer()
{
    gettimeofday(&startTime, 0);
}

timeval Timer::getElapsedTime() const
{
    timeval tv;
    gettimeofday(&tv, 0);

    return subtime(tv, startTime);
}

CUT_NS_END
