#include "magellan/magellan.hpp"
#include <ccinfra/sched/Executor.h>

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    int fib(int n)
    {
        if(n == 0) return 0;
        return n + fib(n-1);
    }

    struct Fib
    {
        Fib(int n) : n(n)
        {
        }

        int operator()() const
        {
            return fib(n);
        }

    private:
        int n;
    };
}


FIXTURE(ExecutorTest)
{
    Executor executor{2};

    TEST("should execute normal function")
	{
	    auto result = executor.execute(fib, 5);
	    ASSERT_THAT(result.get(), eq(15));
	}

	TEST("should execute lambda")
	{
	    const int num = 5;
	    auto result = executor.execute([=](){ return fib(num); });
	    ASSERT_THAT(result.get(), eq(15));
	}

	TEST("should execute functor")
	{
	    auto result = executor.execute(Fib(5));
	    ASSERT_THAT(result.get(), eq(15));
	}

	TEST("should execute muti task concurrently")
	{
	    auto result1 = executor.execute(Fib(5));
	    auto result2 = executor.execute(Fib(6));

	    ASSERT_THAT(result1.get(), eq(15));
	    ASSERT_THAT(result2.get(), eq(21));
	}
};


