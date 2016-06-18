#include "magellan/magellan.hpp"
#include "ccinfra/base/BaseTypes.h"
#include "ccinfra/mem/Placement.h"
#include "ccinfra/base/Keywords.h"
#include "ccinfra/dci/Role.h"
#include <ccinfra/base/NullPtr.h>

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    struct Student
    {
        Student(U32 id) : id(id)
        {
        }

        U32 getId() const
        {
            return id;
        }

    private:
        U32 id;
    };
}

FIXTURE(PlacementTest1)
{
	TEST("should new object on placement memory")
	{
		Placement<Student> studentMemory;

		Student *student = new (studentMemory.alloc()) Student(5);

		ASSERT_THAT(student->getId(), eq(5));
		ASSERT_THAT(studentMemory.getRef().getId(), eq(5));
		ASSERT_THAT(studentMemory->getId(), eq(5));
		ASSERT_THAT((*studentMemory).getId(), eq(5));

		studentMemory.destroy();
	}

	TEST("should new object array on placement")
	{
		const U8 MAX_ENGINE = 5;
		Placement<Student> students[MAX_ENGINE];

		for(int i = 0; i < MAX_ENGINE; i++)
		{
			new (students[i].alloc()) Student(i);
		}

		for(int i = 0; i < MAX_ENGINE; i++)
		{
			ASSERT_THAT(students[i]->getId(), eq(i));
		}
	}
};

namespace
{
    const unsigned int INVALID_ID = 0xFFFFFFFF;

    struct Member
    {
        Member(U32 id) : id(id)
        {
        }

        U32 getId() const
        {
            return id;
        }

    private:
        U32 id;
    };

    struct Object
    {
        Object() : member(__null_ptr)
        {
        }

        void updateId(U32 id)
        {
            if(__NOT_NULL(member)) return;
            member = new (memory.alloc()) Member(id);
        }

        U32 getId() const
        {
            if(__IS_NULL(member)) return INVALID_ID;
            return member->getId();
        }

        ~Object()
        {
            if(__NOT_NULL(member)) memory.destroy();
        }

    private:
        Member* member;
        Placement<Member> memory;
    };
}

FIXTURE(PlacementTest2)
{
	TEST("should delay init the member object in placement")
	{
		Object object;

		ASSERT_THAT(object.getId(), eq(INVALID_ID));

		object.updateId(5);
		ASSERT_THAT(object.getId(), eq(5));
	}
};

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
        ChargeEnergy() : percent(FULL_PERCENT)
        {
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

        bool isExhausted() const
        {
            return ROLE(Energy).isExhausted();
        }

    private:
        U32 produceNum;

    private:
        USE_ROLE(Energy);
    };

    enum WorkerType
    {
        HUMAN,
        ROBOT
    };

    struct WorkerObject : Worker
    {
        WorkerObject(WorkerType type)
        : energy(__null_ptr)
        {
            if(type == HUMAN)
            {
                energy = new (energyMemory.human.alloc()) HumanEnergy();
            }
            else
            {
                energy = new (energyMemory.robot.alloc()) ChargeEnergy();
            }
        }

    private:
        union
        {
            Placement<HumanEnergy>  human;
            Placement<ChargeEnergy> robot;
        }energyMemory;

        Energy *energy;

    private:
        IMPL_ROLE_WITH_OBJ(Energy, *energy);
    };
}

FIXTURE(PlacementTest3)
{
	TEST("should cast to the public role correctly for human")
	{
		WorkerObject human(HUMAN);

		while(!SELF(human, Worker).isExhausted())
		{
			SELF(human, Worker).produce();
		}
		ASSERT_THAT(SELF(human, Worker).getProduceNum(), eq(MAX_CONSUME_TIMES));
	}

	TEST("should cast to the public role correctly for robot")
	{
		WorkerObject robot(ROBOT);

		while(!SELF(robot, Worker).isExhausted())
		{
			SELF(robot, Worker).produce();
		}
		ASSERT_THAT(SELF(robot, Worker).getProduceNum(),
				eq(FULL_PERCENT/CONSUME_PERCENT));
	}
};
