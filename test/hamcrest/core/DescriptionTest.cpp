#include <hamcrest/base/Description.h>
#include <hamcrest/core/helper/IsHelper.h>
#include <assertion/Asserter.h>

USING_HAMCREST_NS

struct DescriptionTest : testing::Test
{
    Description desc;
};

TEST_F(DescriptionTest, bool_false)
{
    desc.appendValue(false);
    ASSERT_THAT(desc.to_s(), is(std::string("<(bool)false>")));
}

TEST_F(DescriptionTest, bool_true)
{
    desc.appendValue(true);
    ASSERT_THAT(desc.to_s(), is(std::string("<(bool)true>")));
}

TEST_F(DescriptionTest, null_integer)
{
    desc.appendValue((void*)0);
    ASSERT_THAT(desc.to_s(), is(std::string("<(void*)nil>")));
}

TEST_F(DescriptionTest, NULL)
{
    desc.appendValue((void*)NULL);
    ASSERT_THAT(desc.to_s(), is(std::string("<(void*)nil>")));
}

TEST_F(DescriptionTest, nullptr)
{
    desc.appendValue(nullptr);
    ASSERT_THAT(desc.to_s(), is(std::string("<(std::nullptr_t)nullptr>")));
}

TEST_F(DescriptionTest, char)
{
    desc.appendValue((char)2);
    ASSERT_THAT(desc.to_s(), is(std::string("<(char)0x2/2>")));
}

TEST_F(DescriptionTest, signed_char)
{
    desc.appendValue((signed char)2);
    ASSERT_THAT(desc.to_s(), is(std::string("<(signed char)0x2/2>")));
}

TEST_F(DescriptionTest, unsigned_char)
{
    desc.appendValue((unsigned char)2);
    ASSERT_THAT(desc.to_s(), is(std::string("<(unsigned char)0x2/2>")));
}

TEST_F(DescriptionTest, short)
{
    desc.appendValue((short)2);
    ASSERT_THAT(desc.to_s(), is(std::string("<(short)0x2/2>")));
}

TEST_F(DescriptionTest, signed_short)
{
    desc.appendValue((signed short)2);
    ASSERT_THAT(desc.to_s(), is(std::string("<(short)0x2/2>")));
}

TEST_F(DescriptionTest, unsigned_short)
{
    desc.appendValue((unsigned short)2);
    ASSERT_THAT(desc.to_s(), is(std::string("<(unsigned short)0x2/2>")));
}

TEST_F(DescriptionTest, int)
{
    desc.appendValue(2);
    ASSERT_THAT(desc.to_s(), is(std::string("<(int)0x2/2>")));
}

TEST_F(DescriptionTest, unsigned_int)
{
    desc.appendValue(2U);
    ASSERT_THAT(desc.to_s(), is(std::string("<(unsigned int)0x2/2>")));
}

TEST_F(DescriptionTest, long)
{
    desc.appendValue(2L);
    ASSERT_THAT(desc.to_s(), is(std::string("<(long)0x2/2>")));
}

TEST_F(DescriptionTest, unsigned_long)
{
    desc.appendValue(2UL);
    ASSERT_THAT(desc.to_s(), is(std::string("<(unsigned long)0x2/2>")));
}

TEST_F(DescriptionTest, c_style_string)
{
    desc.appendValue("hello, world");
    ASSERT_THAT(desc.to_s(), is(std::string("<(char [13])\"hello, world\">")));
}

TEST_F(DescriptionTest, std_string)
{
    desc.appendValue(std::string("hello, world"));
    ASSERT_THAT(desc.to_s(), is(std::string("<(std::string)\"hello, world\">")));
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
