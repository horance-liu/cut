#ifndef H7E147A58_B997_4DC5_B6EB_A014CC6F6C3E
#define H7E147A58_B997_4DC5_B6EB_A014CC6F6C3E

#include <gtest/gtest.h>
#include <hamcrest/base/Matcher.h>
#include <hamcrest/core/IsNil.h>

HAMCREST_NS_BEGIN

template <typename U, typename V>
void assert_that(const U& actual, const Matcher<V>& matcher)
{
    if (!matcher.matches(actual))
    {
        Description desc; 
        
        desc.appendText("Expected: ") \
            .appendDescriptionOf(matcher) \
            .appendText(", but got: ") \
            .appendValue(actual); \

        FAIL() << desc.to_s();
    }
}

#define ASSERT_THAT(actual, matcher) HAMCREST_NS::assert_that(actual, matcher)

HAMCREST_NS_END

#endif
