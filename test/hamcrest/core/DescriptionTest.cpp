#include <hamcrest/base/Description.h>
#include <hamcrest/core/helper/IsHelper.h>
#include <assertion/Asserter.h>

USING_HAMCREST_NS

struct DescriptionTest : testing::Test
{
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

protected:
    Description desc;
};

TEST_F(DescriptionTest, bool_false)
{
    given_description()
        .when_append_value(false)
        .then_result_is("<(bool)false>");
}

TEST_F(DescriptionTest, bool_true)
{
    given_description()
        .when_append_value(true)
        .then_result_is("<(bool)true>");
}

TEST_F(DescriptionTest, null_integer)
{
    given_description()
        .when_append_value((void*)0)
        .then_result_is("<(void*)nil>");
}

TEST_F(DescriptionTest, NULL)
{
    given_description()
        .when_append_value((void*)NULL)
        .then_result_is("<(void*)nil>");
}

TEST_F(DescriptionTest, nullptr)
{
    given_description()
        .when_append_value(nullptr)
        .then_result_is("<(std::nullptr_t)nullptr>");
}

TEST_F(DescriptionTest, char)
{
    given_description()
        .when_append_value((char)2)
        .then_result_is("<(char)0x2/2>");
}

TEST_F(DescriptionTest, signed_char)
{
    given_description()
        .when_append_value((signed char)2)
        .then_result_is("<(signed char)0x2/2>");
}

TEST_F(DescriptionTest, unsigned_char)
{
    given_description()
        .when_append_value((unsigned char)2)
        .then_result_is("<(unsigned char)0x2/2>");
}

TEST_F(DescriptionTest, short)
{
    given_description()
        .when_append_value((short)2)
        .then_result_is("<(short)0x2/2>");
}

TEST_F(DescriptionTest, signed_short)
{
    given_description()
        .when_append_value((signed short)2)
        .then_result_is("<(short)0x2/2>");
}

TEST_F(DescriptionTest, unsigned_short)
{
    given_description()
        .when_append_value((unsigned short)2)
        .then_result_is("<(unsigned short)0x2/2>");
}

TEST_F(DescriptionTest, int)
{
    given_description()
        .when_append_value(2)
        .then_result_is("<(int)0x2/2>");
}

TEST_F(DescriptionTest, unsigned_int)
{
    given_description()
        .when_append_value(2U)
        .then_result_is("<(unsigned int)0x2/2>");
}

TEST_F(DescriptionTest, long)
{
    given_description()
        .when_append_value(2L)
        .then_result_is("<(long)0x2/2>");
}

TEST_F(DescriptionTest, unsigned_long)
{
    given_description()
        .when_append_value(2UL)
        .then_result_is("<(unsigned long)0x2/2>");
}

TEST_F(DescriptionTest, c_style_string)
{
    given_description()
        .when_append_value("hello, world")
        .then_result_is("<(char [13])\"hello, world\">");
}

TEST_F(DescriptionTest, std_string)
{
    given_description()
        .when_append_value(std::string("hello, world"))
        .then_result_is("<(std::string)\"hello, world\">");
}

TEST_F(DescriptionTest, append_text)
{
    desc.appendText("hello")
        .appendText(", ")
        .appendText("world");

    ASSERT_THAT(desc.to_s(), is(std::string("hello, world")));
}

TEST_F(DescriptionTest, append_value_list)
{
    desc.appendValueList("{", ", ", "}", std::vector<int>{1, 2});

    ASSERT_THAT(desc.to_s(), is(std::string("{<(int)0x1/1>, <(int)0x2/2>}")));
}
