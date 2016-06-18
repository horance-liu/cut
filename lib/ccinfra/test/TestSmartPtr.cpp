#include "magellan/magellan.hpp"
#include <ccinfra/mem/SharedObject.h>
#include <ccinfra/mem/SmartPtr.h>
#include <ccinfra/base/Keywords.h>

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    struct Foo : SharedObject
    {
        Foo() : destroyedNum(0)
        {
        }

        int getDestroyNum() const
        {
            return destroyedNum;
        }

        IMPL_ROLE(SharedObject);

    private:
        OVERRIDE(void destroy())
        {
            destroyedNum++;
        }
        OVERRIDE(bool needDestroy())
        {
            return true;
        }

    private:
        int destroyedNum;
    };
}

FIXTURE(SmartPtrTest)
{
	TEST("should ref to the correct addr")
	{
		Foo foo;
		SmartPtr<Foo> pf(&foo);

		ASSERT_THAT(pf.isNull(), be_false());
		ASSERT_THAT(pf.raw(), eq(&foo));
	}

	TEST("should be equal when point to same addr")
	{
		Foo foo;
		SmartPtr<Foo> pf1(&foo);
		SmartPtr<Foo> pf2(&foo);

		ASSERT_THAT(pf1 == pf2, be_true());
	}

	TEST("should increase ref when assign to smart ptr")
	{
		Foo foo;

		{
			SmartPtr<Foo> pf(&foo);
			ASSERT_THAT(foo.getRefCount(), eq(1));
			ASSERT_THAT(foo.getDestroyNum(), eq(0));
		}

		ASSERT_THAT(foo.getRefCount(), eq(0));
		ASSERT_THAT(foo.getDestroyNum(), eq(1));
	}

	TEST("should not destory when ref not equal zero")
	{
		Foo foo;

		SmartPtr<Foo> pf1(&foo);

		{
			SmartPtr<Foo> pf2(&foo);
			ASSERT_THAT(foo.getRefCount(), eq(2));
			ASSERT_THAT(foo.getDestroyNum(), eq(0));
		}

		ASSERT_THAT(foo.getRefCount(), eq(1));
		ASSERT_THAT(foo.getDestroyNum(), eq(0));
	}

	TEST("should add ref when smart ptr construct other smart ptr")
	{
		Foo foo;

		SmartPtr<Foo> pf1(&foo);

		{
			SmartPtr<Foo> pf2(pf1);
			ASSERT_THAT(foo.getRefCount(), eq(2));
			ASSERT_THAT(foo.getDestroyNum(), eq(0));
		}

		ASSERT_THAT(foo.getRefCount(), eq(1));
		ASSERT_THAT(foo.getDestroyNum(), eq(0));
	}

	TEST("should add ref when smart ptr assign to other smart ptr")
	{
		Foo foo;

		SmartPtr<Foo> pf1(&foo);

		{
			SmartPtr<Foo> pf2;
			pf2 = pf1;
			ASSERT_THAT(foo.getRefCount(), eq(2));
			ASSERT_THAT(foo.getDestroyNum(), eq(0));
		}

		ASSERT_THAT(foo.getRefCount(), eq(1));
		ASSERT_THAT(foo.getDestroyNum(), eq(0));
	}
};
