#include <magellan/hamcrest/core/helper/IsHelper.h>
#include <magellan/hamcrest/core/helper/NilHelper.h>
#include <assertion/Asserter.h>

USING_HAMCREST_NS

namespace
{
    void* create_nil_obj1()
    {
        return nullptr;
    }

    int* create_nil_obj2()
    {
        return NULL;
    }

    const int* create_nil_obj3()
    {
        return 0;
    }

    struct Foo
    {
        static Foo* create_nil()
        {
            return nullptr;
        }
    };

    const Foo* nil_foo = Foo::create_nil();
}

TEST(nil, equal_to)
{
    ASSERT_THAT(nullptr, equal_to(nullptr));
    ASSERT_THAT(0, equal_to(NULL));
    ASSERT_THAT(NULL, equal_to(NULL));
    ASSERT_THAT(NULL, equal_to(0));
}

TEST(nil, is)
{
    ASSERT_THAT(nullptr, is(nullptr));
    ASSERT_THAT(nullptr, is(equal_to(nullptr)));

    ASSERT_THAT(0, is(0));
    ASSERT_THAT(NULL, is(NULL));
    ASSERT_THAT(0, is(NULL));
    ASSERT_THAT(NULL, is(0));
}

TEST(nil, nil)
{
    ASSERT_THAT(create_nil_obj1(), nil);
    ASSERT_THAT(create_nil_obj2(), nil);
    ASSERT_THAT(create_nil_obj3(), nil);
    ASSERT_THAT(Foo::create_nil(), nil);
    ASSERT_THAT(nil_foo, nil);

    ASSERT_THAT((void*)NULL, nil);
    ASSERT_THAT((void*)0, nil);
    ASSERT_THAT(nullptr, nil);
}

TEST(nil, is_nil)
{
    ASSERT_THAT(create_nil_obj1(), is(nil));
    ASSERT_THAT(create_nil_obj2(), is(nil));
    ASSERT_THAT(create_nil_obj3(), is(nil));
    ASSERT_THAT(Foo::create_nil(), is(nil));
    ASSERT_THAT(nil_foo, is(nil));
}

namespace
{
    void* create_obj1()
    {
        static int i = 10;
        return &i;
    }

    int* create_obj2()
    {
        static int i = 10;
        return &i;
    }

    const int* create_obj3()
    {
        static int i = 10;
        return &i;
    }

    struct Bar
    {
        static Bar* create()
        {
            static Bar bar;
            return &bar;
        }
    };

    const Bar* bar = Bar::create();
}

TEST(not_nil, is_not_nil)
{
    ASSERT_THAT(create_obj1(), is_not(nil));
    ASSERT_THAT(create_obj2(), is_not(nil));
    ASSERT_THAT(create_obj3(), is_not(nil));
    ASSERT_THAT(Bar::create(), is_not(nil));
    ASSERT_THAT(bar, is_not(nil));
}
