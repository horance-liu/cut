#include "magellan/magellan.hpp"
#include <ccinfra/sched/ThreadData.h>

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    struct ThreadInfo
    {
        static unsigned int getCurrentId()
        {
            return index;
        }

        static void setCurrentId(unsigned int id)
        {
            index = id;
        }

        const static unsigned int MAX_THREAD_NUM = 2;

    private:
        static unsigned int index;
    };

    unsigned int ThreadInfo::index = 0;
}

FIXTURE(ThreadDataTest)
{
    ThreadData<int, ThreadInfo> data;

	TEST("should write the correct thread data when default thread id")
	{
		*data = 2;

		ASSERT_THAT(*data, eq(2));
		ASSERT_THAT(data[0], eq(2));
	}

	TEST("should write the correct thread data when change the current thread id")
	{
		ThreadInfo::setCurrentId(1);

		*data = 5;

		ASSERT_THAT(*data, eq(5));
		ASSERT_THAT(data[1], eq(5));
	}
};
