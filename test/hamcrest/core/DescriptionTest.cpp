#include <gtest/gtest.h>
#include <hamcrest/base/Description.h>

USING_HAMCREST_NS

struct DescriptionTest : testing::Test
{
    Description desc;
};

TEST_F(DescriptionTest, should)
{
    desc.appendValueList("{", ", ", "}", std::vector<int>{1, 2, 3});

    printf("%s\n", desc.to_s().c_str());
}
