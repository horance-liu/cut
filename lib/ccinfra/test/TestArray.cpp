#include "magellan/magellan.hpp"
#include "ccinfra/ctnr/array/Array.h"

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    struct PlainObject
    {
        int a;
        int b;
    };

    const int INVALID_VALUE = 0xFF;

    struct Object
    {
        Object() : value(INVALID_VALUE)
        {
        }

        Object(int value)
        :value(value)
        {
        }

        int getValue() const
        {
            return value;
        }

        void update(U8 v)
        {
            value = v;
        }

    private:
        U8 value;
    };
}

FIXTURE(ArrayTest)
{
	TEST("should define plain object array")
	{
	    Array<PlainObject, 2> objects;

	    objects[0].a = 1;
	    objects[1].b = 2;

	    ASSERT_THAT(objects.size(), eq(2));
	    ASSERT_THAT(objects[0].a, eq(1));
	    ASSERT_THAT(objects[1].b, eq(2));
	}

    TEST("should define object array with default constructor")
	{
	    Array<Object, 2> objects;

	    ASSERT_THAT(objects[0].getValue(), eq(INVALID_VALUE));
	    ASSERT_THAT(objects[1].getValue(), eq(INVALID_VALUE));
	}

	TEST("should define object array with para constructor")
	{
	    Array<Object, 2> objects(5);

	    ASSERT_THAT(objects[0].getValue(), eq(5));
	    ASSERT_THAT(objects[1].getValue(), eq(5));
	}

    TEST("should invoke unconst method of array elem")
	{
	    Array<Object, 2> objects(5);

	    objects[1].update(10);

	    ASSERT_THAT(objects[0].getValue(), eq(5));
	    ASSERT_THAT(objects[1].getValue(), eq(10));
	}

    TEST("should emplace a array elem")
	{
	    Array<Object, 2> objects;

	    objects.emplace(1, 5);

	    ASSERT_THAT(objects[0].getValue(), eq(INVALID_VALUE));
	    ASSERT_THAT(objects[1].getValue(), eq(5));
	}

    TEST("should use the iterator of array")
	{
	    typedef Array<Object, 2> ThisArray;
	    ThisArray objects;


	    ThisArray::Iterator i = objects.begin();
	    ASSERT_THAT(i->getValue(), eq(INVALID_VALUE));

	    objects[1].update(5);
	    i++;
	    ASSERT_THAT(i->getValue(), eq(5));

	    i->update(10);
	    ASSERT_THAT(objects[1].getValue(), eq(10));

	    ASSERT_THAT(i, ne(objects.end()));
	    ASSERT_THAT(++i, eq(objects.end()));
	}

    TEST("should travel array")
	{
	    typedef Array<Object, 2> ThisArray;
	    ThisArray objects(10);

	    objects[1].update(5);

	    U32 sum = 0;
	    ARRAY_FOREACH(ThisArray, i, objects)
	    {
	        sum += i->getValue();
	    }
	    ASSERT_THAT(sum, eq(15));
	}
};


