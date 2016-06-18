#include "magellan/magellan.hpp"
#include <ccinfra/mem/AutoMsg.h>

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    struct LargeMsg
    {
        U8 msgBuff[16 * 1024];
    };
}

FIXTURE(AutoMsgTest)
{
	TEST("should alloc auto msg not in stack")
	{
	    AutoMsg<LargeMsg> msg;

	    ASSERT_THAT(MsgAllocator::withIn(msg.getPointer()), be_true());
	}
};


