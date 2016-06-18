#include "magellan/magellan.hpp"
#include "ccinfra/dci/Role.h"
#include "ccinfra/base/BaseTypes.h"
#include "ccinfra/base/Keywords.h"

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    DEFINE_ROLE(Energy)
    {
        ABSTRACT(void consume());
        ABSTRACT(bool isExhausted() const);
    };

	const int MAX_CONSUME_TIMES = 10;

	struct HumanEnergy : Energy
    {
        HumanEnergy()
        : isHungry(false), consumeTimes(0)
        {
        }

        void supplyByFood()
        {
            isHungry = false;
            consumeTimes = 0;
        }

    private:
        OVERRIDE(void consume())
        {
            consumeTimes++;

            if(consumeTimes >= MAX_CONSUME_TIMES)
            {
                isHungry = true;
            }
        }

        OVERRIDE(bool isExhausted() const)
        {
            return isHungry;
        }

    private:
        bool isHungry;
        U8 consumeTimes;
    };

	const int FULL_PERCENT = 100;
	const int CONSUME_PERCENT = 1;

    struct ChargeEnergy : Energy
    {
        ChargeEnergy() : percent(0)
        {
        }

        void charge()
        {
            percent = FULL_PERCENT;
        }

    private:
        OVERRIDE(void consume())
        {
            if(percent > 0)
                percent -= CONSUME_PERCENT;
        }

        OVERRIDE(bool isExhausted() const)
        {
            return percent == 0;
        }

    private:
        U8 percent;
    };

    DEFINE_ROLE(Worker)
    {
        Worker() : produceNum(0)
        {
        }

        void produce()
        {
            if(ROLE(Energy).isExhausted()) return;

            produceNum++;

            ROLE(Energy).consume();
        }

        U32 getProduceNum() const
        {
            return produceNum;
        }

    private:
        U32 produceNum;

    private:
        USE_ROLE(Energy);
    };

    struct Human : Worker
                 , HumanEnergy
    {
    private:
        IMPL_ROLE(Energy);
    };

    struct Robot : Worker
                 , ChargeEnergy
    {
    private:
        IMPL_ROLE(Energy);
    };
}

FIXTURE(RoleTest)
{
	TEST("should cast to the public role correctly for human")
	{
		Human human;

		while(!SELF(human, Energy).isExhausted())
		{
			SELF(human, Worker).produce();
		}
		ASSERT_THAT(SELF(human, Worker).getProduceNum(), eq(MAX_CONSUME_TIMES));

		human.supplyByFood();
		ASSERT_THAT(SELF(human, Energy).isExhausted(), be_false());
	}

	TEST("should cast to the public role correctly for robot")
	{
		Robot robot;

		SELF(robot, ChargeEnergy).charge();

		while(!SELF(robot, Energy).isExhausted())
		{
			SELF(robot, Worker).produce();
		}
		ASSERT_THAT(SELF(robot, Worker).getProduceNum(),
				eq(FULL_PERCENT/CONSUME_PERCENT));
	}
};
