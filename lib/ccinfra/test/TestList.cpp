#include "magellan/magellan.hpp"
#include <ccinfra/ctnr/list/List.h>
#include <ccinfra/ctnr/list/ListElem.h>
#include <ccinfra/base/NullPtr.h>

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    struct Foo : ListElem<Foo>
    {
        Foo(int a) : x(a)
        {
        }

        int getValue() const
        {
            return x;
        }

    private:
        int x;
    };
}

FIXTURE(ListTest)
{
	TEST("should be empty when init")
	{
		ASSERT_THAT(__IS_NULL(elems.getFirst()), be_true());
	    ASSERT_THAT(__IS_NULL(elems.getLast()), be_true());
	    ASSERT_THAT(elems.isEmpty(), be_true());
	    ASSERT_THAT(elems.size(), eq(0));
	}

	TEST("should be get elem when list is not empty")
	{
	    Foo elem(1);

	    elems.pushBack(elem);

	    ASSERT_THAT(elems.isEmpty(), be_false());
	    ASSERT_THAT(elems.size(), eq(1));
	    ASSERT_THAT(elems.getFirst(), eq(&elem));
	    ASSERT_THAT(elems.getLast(), eq(&elem));

	    Foo* first = elems.popFront();
	    ASSERT_THAT(first->getValue(), eq(1));
	    ASSERT_THAT(elems.isEmpty(), be_true());
	}

	TEST("should travel the list")
	{
	    Foo elem1(1), elem2(2), elem3(3);

	    elems.pushBack(elem1);
	    elems.pushBack(elem2);
	    elems.pushBack(elem3);

	    int i = 1;
	    LIST_FOREACH(Foo, elem, elems)
	    {
	        ASSERT_THAT(elem->getValue(), eq(i++));
	    }
	}

	TEST("should point to the correct addr when get next")
	{
	    Foo elem(1);
	    elems.pushBack(elem);

	    ASSERT_THAT(elems.begin().getValue(), eq(&elem));
	    ASSERT_THAT(elems.end().getValue(), ne(&elem));
	    List<Foo>::Iterator p = elems.begin();
	    ASSERT_THAT(elems.getNext(p), eq(elems.end()));
	}

    List<Foo> elems;
};


