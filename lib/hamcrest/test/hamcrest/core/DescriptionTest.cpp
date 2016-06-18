#include <hamcrest/base/Description.h>
#include <hamcrest/core/def/IsDef.h>
#include <cut/cut.hpp>

USING_HAMCREST_NS

FIXTURE(DescriptionTest)
{
    Description desc;

    DescriptionTest& given_description()
    {
        return *this;
    }

    template <typename T>
    DescriptionTest& when_append_value(const T& val)
    {
        desc.appendValue(val);
        return *this;
    }

    void then_result_is(const std::string& result)
    {
        ASSERT_THAT(desc.to_s(), is(result));
    }

    TEST("false")
    {
        given_description()
            .when_append_value(false)
            .then_result_is("<false: bool>");
    }

    TEST("true")
    {
        given_description()
            .when_append_value(true)
            .then_result_is("<true: bool>");
    }

    TEST("null integer")
    {
        given_description()
            .when_append_value((void*)0)
            .then_result_is("<nil: void*>");
    }

    TEST("NULL")
    {
        given_description()
            .when_append_value((void*)NULL)
            .then_result_is("<nil: void*>");
    }

    TEST("nullptr")
    {
        given_description()
            .when_append_value(nullptr)
            .then_result_is("<nullptr: std::nullptr_t>");
    }

    TEST("char")
    {
        given_description()
            .when_append_value((char)2)
            .then_result_is("<2: char>");
    }

    TEST("signed char")
    {
        given_description()
            .when_append_value((signed char)2)
            .then_result_is("<2: signed char>");
    }

    TEST("unsigned char")
    {
        given_description()
            .when_append_value((unsigned char)2)
            .then_result_is("<2: unsigned char>");
    }

    TEST("short")
    {
        given_description()
            .when_append_value((short)2)
            .then_result_is("<2: short>");
    }

    TEST("signed short")
    {
        given_description()
            .when_append_value((signed short)2)
            .then_result_is("<2: short>");
    }

    TEST("unsigned short")
    {
        given_description()
            .when_append_value((unsigned short)2)
            .then_result_is("<2: unsigned short>");
    }

    TEST("int")
    {
        given_description()
            .when_append_value(2)
            .then_result_is("<2: int>");
    }

    TEST("unsigned int")
    {
        given_description()
            .when_append_value(2U)
            .then_result_is("<2: unsigned int>");
    }

    TEST("long")
    {
        given_description()
            .when_append_value(2L)
            .then_result_is("<2: long>");
    }

    TEST("unsigned long")
    {
        given_description()
            .when_append_value(2UL)
            .then_result_is("<2: unsigned long>");
    }

    TEST("c style string")
    {
        given_description()
            .when_append_value("hello, world")
            .then_result_is("<hello, world: char [13]>");
    }

    TEST("std::string")
    {
        given_description()
            .when_append_value(std::string("hello, world"))
            .then_result_is("<hello, world: std::string>");
    }

    TEST("append text")
    {
        desc.appendText("hello")
            .appendText(", ")
            .appendText("world");

        ASSERT_THAT(desc.to_s(), is(std::string("hello, world")));
    }

    TEST("append value list")
    {
        desc.appendValueList("{", ", ", "}", std::vector<int>{1, 2});

        ASSERT_THAT(desc.to_s(), is(std::string("{<1: int>, <2: int>}")));
    }
};
