#include "magellan/magellan.hpp"
#include <ccinfra/mem/PlainTransData.h>

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    struct Foo
    {
       int a, b;
    };
}

FIXTURE(PlainTransDataTest)
{
	SETUP()
	{
		foo.a = 10;
		foo.b = 20;
	}

	const int* getConstPointer() const
	{
	  return intData.operator->();
	}

	const int& getConstReference() const
	{
	  return *intData;
	}

	void enableModifiable()
	{
	   intData.update(10);
	   intData.confirm();
	   intData.modify();
	}

	PlainTransData<int> intData;
	PlainTransData<Foo> fooData;

	Foo foo;

	TEST("an uninitialized trans data should be invalid")
	{
		ASSERT_THAT(intData.isPresent(), be_false());
	}

	TEST("an uninitialized trans data should be null if accessed by pointer")
	{
		ASSERT_THAT(0 == intData.operator->(), be_true());
	}

	TEST("an uninitialized trans data should be null if accessed by a constant pointer")
	{
		ASSERT_THAT(0 == getConstPointer(), be_true());
	}

	TEST("once set value it should become valid")
	{
		intData.update(10);
		ASSERT_THAT(intData.isPresent(), be_true());
	}

	TEST("once set value it should be able to be accessed by reference")
	{
		intData.update(10);
		ASSERT_THAT(10 == getConstReference(), be_true());
	}

	TEST("if revert a updated value should become invalid")
	{
		intData.update(10);
		intData.revert();

		ASSERT_THAT(intData.isPresent(), be_false());
	}

	TEST("before a updated value is confirmed if it reverted should become invalid again")
	{
		intData.update(10);
		intData.update(20);
		intData.revert();

		ASSERT_THAT(intData.isPresent(), be_false());
	}

	TEST("once a updated value is confirmed it should will become valid")
	{
		intData.update(10);
		intData.confirm();

		ASSERT_THAT(intData.isPresent(), be_true());
	}

	TEST("a confirmed value can not be reverted")
	{
		intData.update(10);
		intData.confirm();
		intData.revert();

		ASSERT_THAT(intData.isPresent(), be_true());
		ASSERT_THAT(10 == (*intData), be_true());
	}

	TEST("a confirmed value can be updated again")
	{
		intData.update(10);
		intData.confirm();
		intData.update(20);

		ASSERT_THAT(intData.isPresent(), be_true());
		ASSERT_THAT(20 == (*intData), be_true());
	}

	TEST("if a confirmed value is updated again then reverting should be able to rollback")
	{
		intData.update(10);
		intData.confirm();
		intData.update(20);
		intData.revert();

		ASSERT_THAT(intData.isPresent(), be_true());
		ASSERT_THAT(10 == (*intData), be_true());
	}

	TEST("once a confirmed value is reset it should become invalid")
	{
		intData.update(10);
		intData.confirm();
		intData.reset();

		ASSERT_THAT(intData.isPresent(), be_false());
	}

	TEST("an unstable data should not be able to be modified")
	{
		intData.update(10);

		ASSERT_THAT(intData.modify(), ne(CCINFRA_SUCCESS));
	}

	TEST("a stable data should be able to be modified")
	{
		intData.update(10);
		intData.confirm();

		ASSERT_THAT(intData.modify(), eq(CCINFRA_SUCCESS));
	}

	TEST("after clone for modification it is value keep unchanged")
	{
		enableModifiable();
		ASSERT_THAT(*intData, eq(10));
	}

	TEST("after clone for modification should be able modify actually")
	{
		enableModifiable();
		(*intData) = 20;

		ASSERT_THAT(*intData, eq(20));
	}

	TEST("after modification if revert should roll back")
	{
		enableModifiable();
		(*intData) = 20;
		intData.revert();

		ASSERT_THAT(*intData, eq(10));
	}

	TEST("for an uninitialized trans data its old value should be invalid")
	{
		ASSERT_THAT(fooData.isOldPresent(), be_false());
	}

	TEST("for an initialized trans data its old value is still be invalid")
	{
		fooData.update(foo);
		ASSERT_THAT(fooData.isOldPresent(), be_false());
	}

	TEST("for an initialized PlainTransData after confirmation its old value is still be invalid")
	{
		fooData.update(foo);
		fooData.confirm();

		ASSERT_THAT(fooData.isOldPresent(), be_false());
	}

	TEST("after confirmation if update again its old value should be valid")
	{
		fooData.update(foo);
		fooData.confirm();

		foo.a = 1;
		foo.b = 2;

		fooData.update(foo);

		ASSERT_THAT(fooData.isOldPresent(), be_true());
	}

	TEST("after confirmation if update again its old value should be the previous one")
	{
		fooData.update(foo);
		fooData.confirm();

		foo.a = 1;
		foo.b = 2;

		fooData.update(foo);

		ASSERT_THAT(fooData.getOldValue().a, eq(10));
		ASSERT_THAT(fooData.getOldValue().b, eq(20));
	}

	TEST("after confirmation if update again its new value should be the new one")
	{
		fooData.update(foo);
		fooData.confirm();

		foo.a = 1;
		foo.b = 2;

		fooData.update(foo);

		ASSERT_THAT(fooData->a, eq(1));
		ASSERT_THAT(fooData->b, eq(2));
	}
};
