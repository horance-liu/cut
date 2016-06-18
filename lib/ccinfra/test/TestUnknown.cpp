#include "magellan/magellan.hpp"
#include "ccinfra/base/BaseTypes.h"
#include "ccinfra/dci/Unknown.h"
#include "ccinfra/base/NullPtr.h"

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    UNKNOWN_INTERFACE(Worker, 0x1234)
    {
        Worker() : produceNum(0)
        {
        }

        void produce()
        {
            produceNum++;
        }

        U32 getProduceNum() const
        {
            return produceNum;
        }

    private:
        U32 produceNum;
    };

    UNKNOWN_INTERFACE(SleepInfo, 0x2345)
    {
        SleepInfo() : sleeping(false)
        {
        }

        void sleep()
        {
            sleeping = true;
        }

        void wakeup()
        {
            sleeping = false;
        }

        bool isSleeping() const
        {
            return sleeping;
        }

    private:
        bool sleeping;
    };

    UNKNOWN_INTERFACE(ChargeInfo, 0x3521)
    {
        ChargeInfo() : percent(0)
        {
        }

        void charge()
        {
            percent = 100;
        }

        void cosume()
        {
            percent -= 10;
        }

        bool isNeedCharge() const
        {
            return percent == 0;
        }

    private:
        U8 percent;
    };

    struct Human : dci::Unknown
                 , private Worker
                 , private SleepInfo
    {
        BEGIN_INTERFACE_TABLE()
            __HAS_INTERFACE(Worker)
            __HAS_INTERFACE(SleepInfo)
        END_INTERFACE_TABLE()
    };

    struct Robot : dci::Unknown
                 , private Worker
                 , private ChargeInfo
    {
        BEGIN_INTERFACE_TABLE()
            __HAS_INTERFACE(Worker)
            __HAS_INTERFACE(ChargeInfo)
        END_INTERFACE_TABLE()
    };
}

FIXTURE(UnknownTest)
{
    TEST("should cast to the exist interface")
	{
	    Human human;
	    dci::Unknown * unknown = &human;

	    Worker* worker = dci::unknown_cast<Worker>(unknown);
	    ASSERT_THAT(__NOT_NULL(worker), be_true());

	    worker->produce();
	    ASSERT_THAT(worker->getProduceNum(), eq(1));

	    SleepInfo * info = dci::unknown_cast<SleepInfo>(unknown);
	    ASSERT_THAT(__NOT_NULL(info), be_true());

	    info->sleep();
	    ASSERT_THAT(info->isSleeping(), be_true());

	    info->wakeup();
	    ASSERT_THAT(info->isSleeping(), be_false());
	}

    TEST("should return null when cast to unexist interface")
	{
	    Robot robot;
	    dci::Unknown * unknown = &robot;

	    Worker* worker = dci::unknown_cast<Worker>(unknown);
	    ASSERT_THAT(__NOT_NULL(worker), be_true());

	    SleepInfo * info = dci::unknown_cast<SleepInfo>(unknown);
	    ASSERT_THAT(__IS_NULL(info), be_true());
	}
};


