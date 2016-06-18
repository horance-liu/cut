#include "magellan/magellan.hpp"
#include <ccinfra/mem/TransData.h>
#include <stdlib.h>

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    static unsigned int alloc_blocks = 0;

    struct ObjectInfo
    {
        ObjectInfo() : value(0xFF) {}
        ObjectInfo(int value) : value(value) {}

        int getValue() const
        {
            return value;
        }

        bool operator==(const ObjectInfo& rhs) const
        {
            return value == rhs.value;
        }

        bool operator!=(const ObjectInfo& rhs) const
        {
            return value != rhs.value;
        }

        void* operator new(size_t size)
        {
            alloc_blocks++;
            return ::malloc(size);
        }

        void operator delete(void* p)
        {
            if(p != 0)
            {
                if(alloc_blocks == 0) 
                {
                    throw std::exception();
                }

                alloc_blocks--;
                ::free(p);
            }
        }
    private:
        int value;
    };

    struct Object
    {
        Object() : info(0) {}
        Object(int value) : info(new ObjectInfo(value)) {}

        Object& operator=(const Object& rhs)
        {
            info = rhs.info;
            return *this;
        }

        Status copyTo(Object& rhs)
        {
            CCINFRA_ASSERT_VALID_PTR(info);

            if (rhs.info == 0) rhs.info = new ObjectInfo(*info);
            else *rhs.info = *info;

            return CCINFRA_SUCCESS;
        }

        void reset()
        {
            delete info;
            info = 0;
        }

        bool operator==(const Object& rhs) const
        {
            if(info == 0 && rhs.info == 0) return true;

            if(info != 0 && rhs.info != 0)
            {
                return *info == *rhs.info;
            }

            return false;
        }

        bool operator!=(const Object& rhs) const
        {
            return !(*this == rhs);
        }

        int getValue() const
        {
            return info == 0 ? 0xFF : info->getValue();
        }

    private:
        ObjectInfo *info;
    };

}

FIXTURE(TestInitTransData)
{
    TransData<Object> data;

    TEST("the state should be correct for an uninitialized trans data")
    {
        assertInit();
    }

    TEST("should in NEW state after updating")
    {
        data.update(Object(2));

        assertUpdated();
    }

    TEST("should in NEW state after force updating")
    {
        data.forceUpdate();
        data.update(Object(2));

        assertUpdated();
    }

    TEST("should in ACTIVE state after updating then confirming")
    {
        data.update(Object(2));
        data.confirm();

        ASSERT_THAT(data.isStable(), be_true());

        ASSERT_THAT(data.isPresent(), be_true());
        ASSERT_THAT(data->getValue(), eq(2));

        ASSERT_THAT(data.isOldPresent(), be_false());
        ASSERT_THAT(data.isChanged(), be_false());
        ASSERT_THAT(data.isChanged(true), be_true());
        ASSERT_THAT(alloc_blocks, eq(1));
    }

    TEST("should return to INIT after updating then reverting")
    {
        data.update(Object(2));
        data.revert();

        assertInit();
    }

    TEST("touch should have no effect")
    {
        data.touch();

        assertInit();
    }

    TEST("release should have no effect")
    {
        data.release();

        assertInit();
    }

    TEST("reset should have no effect")
    {
        data.reset();

        assertInit();
    }

    TEST("should not allow to modify")
    {
        ASSERT_THAT(data.modify(), ne(CCINFRA_SUCCESS));

        assertInit();
    }

    void assertInit()
    {
    	ASSERT_THAT(data.isStable(), be_true());

    	ASSERT_THAT(data.isPresent(), be_false());
    	ASSERT_THAT(data.isOldPresent(), be_false());
    	ASSERT_THAT(data.isChanged(), be_false());
    	ASSERT_THAT(data.isChanged(true), be_false());
        ASSERT_THAT(alloc_blocks, eq(0));
    }

    void assertUpdated()
    {
    	ASSERT_THAT(data.isStable(), be_false());

    	ASSERT_THAT(data.isPresent(), be_true());
        ASSERT_THAT(data->getValue(), eq(2));

        ASSERT_THAT(data.isOldPresent(), be_false());
        ASSERT_THAT(data.isChanged(), be_true());
        ASSERT_THAT(data.isChanged(true), be_true());
        ASSERT_THAT(alloc_blocks, eq(1));
    }
};



//////////////////////////////////////////////////////////////////////////
FIXTURE(TestActiveTransData)
{
    TransData<Object> data;

    SETUP()
    {
        data.update(Object(2));
        data.confirm();
    }

    void assertInit()
    {
        ASSERT_THAT(data.isStable(), be_true());

        ASSERT_THAT(data.isPresent(), be_false());
        ASSERT_THAT(data.isOldPresent(), be_false());
        ASSERT_THAT(data.isChanged(), be_false());
        ASSERT_THAT(data.isChanged(true), be_false());
        ASSERT_THAT(alloc_blocks, eq(0));
    }

    void update()
    {
        data.update(Object(3));

        ASSERT_THAT(data.isStable(), be_false());

        ASSERT_THAT(data.isPresent(), be_true());
        ASSERT_THAT(data->getValue(), eq(3));

        ASSERT_THAT(data.isOldPresent(), be_true());
        ASSERT_THAT(data.getOldValue().getValue(), eq(2));

        ASSERT_THAT(data.isChanged(), be_true());
        ASSERT_THAT(data.isChanged(true), be_true());
        ASSERT_THAT(alloc_blocks, eq(2));
    }

	TEST("after reset should return to idle")
	{
		data.reset();
		assertInit();
	}

	TEST("should in MODIFIED state after updating")
	{
		update();
	}

	TEST("should in MODIFIED state after force updating")
	{
		data.forceUpdate();
		update();
	}

	TEST("should in ACTIVE state after updating and confirming")
	{
		data.update(Object(3));
		data.confirm();

		ASSERT_THAT(data.isStable(), be_true());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(3));

		ASSERT_THAT(data.isOldPresent(), be_false());

		ASSERT_THAT(data.isChanged(), be_false());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(1));
	}

	TEST("should not be changed after updating a identical value")
	{
		data.update(Object(2));

		ASSERT_THAT(data.isStable(), be_false());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isOldPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isChanged(), be_false());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(2));
	}

	TEST("should be able to modify")
	{
		ASSERT_THAT(data.modify(), eq(CCINFRA_SUCCESS));

		ASSERT_THAT(data.isStable(), be_false());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isOldPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isChanged(), be_false());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(2));
	}

	TEST("should in ACTIVE state after updating and reverting")
	{
		data.update(Object(3));
		data.revert();

		ASSERT_THAT(data.isStable(), be_true());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isOldPresent(), be_false());

		ASSERT_THAT(data.isChanged(), be_false());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(1));
	}

	TEST("should in TOUCHED state after touch")
	{
		data.touch();

		ASSERT_THAT(data.isStable(), be_false());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isOldPresent(), be_false());

		ASSERT_THAT(data.isChanged(), be_true());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(1));
	}

	TEST("should in RELEASED state after release")
	{
		data.release();

		ASSERT_THAT(data.isStable(), be_false());

		ASSERT_THAT(data.isPresent(), be_false());

		ASSERT_THAT(data.isOldPresent(), be_true());
		ASSERT_THAT(data.getOldValue().getValue(), eq(2));

		ASSERT_THAT(data.isChanged(), be_true());
		ASSERT_THAT(data.isChanged(true), be_false());
		ASSERT_THAT(alloc_blocks, eq(1));

		data.confirm();

		assertInit();
	}

};

//////////////////////////////////////////////////////////////////////////
FIXTURE(TestTouchTransData)
{
    TransData<Object> data;

    SETUP()
    {
        data.update(Object(2));
        data.confirm();
        data.touch();
    }

    void assertInit()
    {
        ASSERT_THAT(data.isStable(), be_true());

        ASSERT_THAT(data.isPresent(), be_false());
        ASSERT_THAT(data.isOldPresent(), be_false());
        ASSERT_THAT(data.isChanged(), be_false());
        ASSERT_THAT(data.isChanged(true), be_false());
        ASSERT_THAT(alloc_blocks, eq(0));
    }


	TEST("should be in shadow state")
	{
		ASSERT_THAT(data.isStable(), be_false());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isOldPresent(), be_false());

		ASSERT_THAT(data.isChanged(), be_true());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(1));

		data.confirm();

		ASSERT_THAT(data.isStable(), be_true());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isOldPresent(), be_false());

		ASSERT_THAT(data.isChanged(), be_false());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(1));
	}

	TEST("should not allow modify")
	{
		ASSERT_THAT(data.modify(), ne(CCINFRA_SUCCESS));

		ASSERT_THAT(data.isStable(), be_false());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isOldPresent(), be_false());

		ASSERT_THAT(data.isChanged(), be_true());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(1));
	}

	TEST("should be in shadow state after updating")
	{
		data.update(Object(2));

		ASSERT_THAT(data.isStable(), be_false());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isOldPresent(), be_true());
		ASSERT_THAT(data.getOldValue().getValue(), eq(2));

		ASSERT_THAT(data.isChanged(), be_true());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(2));
	}

	TEST("should use new data after updating")
	{
		data.update(Object(3));

		ASSERT_THAT(data.isStable(), be_false());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(3));

		ASSERT_THAT(data.isOldPresent(), be_true());
		ASSERT_THAT(data.getOldValue().getValue(), eq(2));

		ASSERT_THAT(data.isChanged(), be_true());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(2));
	}

	TEST("should in ACTIVE state after confirm")
	{
		data.confirm();

		ASSERT_THAT(data.isStable(), be_true());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isOldPresent(), be_false());

		ASSERT_THAT(data.isChanged(), be_false());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(1));
	}

	TEST("should in ACTIVE state after reverting")
	{
		data.revert();

		ASSERT_THAT(data.isStable(), be_true());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isOldPresent(), be_false());

		ASSERT_THAT(data.isChanged(), be_false());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(1));
	}

	TEST("should in RELEASED state after releasing")
	{
		data.release();

		ASSERT_THAT(data.isStable(), be_false());

		ASSERT_THAT(data.isPresent(), be_false());

		ASSERT_THAT(data.isOldPresent(), be_true());
		ASSERT_THAT(data.getOldValue().getValue(), eq(2));

		ASSERT_THAT(data.isChanged(), be_true());
		ASSERT_THAT(data.isChanged(true), be_false());
		ASSERT_THAT(alloc_blocks, eq(1));

		data.confirm();
		assertInit();
	}

	TEST("should in ACTIVE state after releasing and reverting")
	{
		data.release();
		data.revert();

		ASSERT_THAT(data.isStable(), be_true());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isOldPresent(), be_false());

		ASSERT_THAT(data.isChanged(), be_false());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(1));
	}

	TEST("should in IDLE state after reset")
	{
		data.reset();
		assertInit();
	}
};

//////////////////////////////////////////////////////////////////////////
FIXTURE(TestReleaseTransData)
{
    TransData<Object> data;

    SETUP()
    {
        data.update(Object(2));
        data.confirm();
        data.release();
    }

    void assertInit()
    {
    	ASSERT_THAT(data.isStable(), be_true());

    	ASSERT_THAT(data.isPresent(), be_false());
    	ASSERT_THAT(data.isOldPresent(), be_false());
    	ASSERT_THAT(data.isChanged(), be_false());
    	ASSERT_THAT(data.isChanged(true), be_false());
        ASSERT_THAT(alloc_blocks, eq(0));
    }

	TEST("should in IDLE state after reseting")
	{
		data.reset();
		assertInit();
	}

	TEST("should in IDLE state after confirming")
	{
		data.confirm();
		assertInit();
	}

	TEST("should in ACTIVE state after reverting")
	{
		data.revert();

		ASSERT_THAT(data.isStable(), be_true());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isOldPresent(), be_false());

		ASSERT_THAT(data.isChanged(), be_false());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(1));
	}

	TEST("should in RELEASED state")
	{
		ASSERT_THAT(data.isStable(), be_false());

		ASSERT_THAT(data.isPresent(), be_false());

		ASSERT_THAT(data.isOldPresent(), be_true());
		ASSERT_THAT(data.getOldValue().getValue(), eq(2));

		ASSERT_THAT(data.isChanged(), be_true());
		ASSERT_THAT(data.isChanged(true), be_false());
		ASSERT_THAT(alloc_blocks, eq(1));
	}

	TEST("should in SHADOWN state after updating")
	{
		data.update(Object(2));

		ASSERT_THAT(data.isStable(), be_false());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isOldPresent(), be_true());
		ASSERT_THAT(data.getOldValue().getValue(), eq(2));

		ASSERT_THAT(data.isChanged(), be_true());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(2));
	}

	TEST("should use new value state after updating")
	{
		data.update(Object(3));

		ASSERT_THAT(data.isStable(), be_false());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(3));

		ASSERT_THAT(data.isOldPresent(), be_true());
		ASSERT_THAT(data.getOldValue().getValue(), eq(2));

		ASSERT_THAT(data.isChanged(), be_true());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(2));
	}

	TEST("should in ACTIVE state after updating and reverting")
	{
		data.update(Object(3));
		data.revert();

		ASSERT_THAT(data.isStable(), be_true());

		ASSERT_THAT(data.isPresent(), be_true());
		ASSERT_THAT(data->getValue(), eq(2));

		ASSERT_THAT(data.isOldPresent(), be_false());

		ASSERT_THAT(data.isChanged(), be_false());
		ASSERT_THAT(data.isChanged(true), be_true());
		ASSERT_THAT(alloc_blocks, eq(1));
	}

	TEST("should not allow modify")
	{
		ASSERT_THAT(data.modify(), ne(CCINFRA_SUCCESS));
	}

	TEST("should have no effect for touching")
	{
		data.touch();

		ASSERT_THAT(data.isStable(), be_false());

		ASSERT_THAT(data.isPresent(), be_false());

		ASSERT_THAT(data.isOldPresent(), be_true());
		ASSERT_THAT(data.getOldValue().getValue(), eq(2));

		ASSERT_THAT(data.isChanged(), be_true());
		ASSERT_THAT(data.isChanged(true), be_false());
		ASSERT_THAT(alloc_blocks, eq(1));
	}

	TEST("should have no effect for releasing")
	{
		data.release();

		ASSERT_THAT(data.isStable(), be_false());

		ASSERT_THAT(data.isPresent(), be_false());

		ASSERT_THAT(data.isOldPresent(), be_true());
		ASSERT_THAT(data.getOldValue().getValue(), eq(2));

		ASSERT_THAT(data.isChanged(), be_true());
		ASSERT_THAT(data.isChanged(true), be_false());
		ASSERT_THAT(alloc_blocks, eq(1));
	}
};
