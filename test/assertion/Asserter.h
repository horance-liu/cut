#ifndef H7E147A58_B997_4DC5_B6EB_A014CC6F6C3E
#define H7E147A58_B997_4DC5_B6EB_A014CC6F6C3E

#include <gtest/gtest.h>
#include <magellan/hamcrest/base/Matcher.h>
#include <magellan/hamcrest/base/Description.h>

HAMCREST_NS_BEGIN

template <typename U, typename V>
void assert_that(const U& actual, const Matcher<V>& matcher)
{
    if (!matcher.matches(actual))
    {
        Description desc; 
        
        desc.appendText("\nExpected: ")
            .appendDescriptionOf(matcher)
            .appendText("\n     but: ");

        matcher.describeMismatch(actual, desc);

        FAIL() << desc.to_s();
    }
}

#define ASSERT_THAT(actual, matcher) HAMCREST_NS::assert_that(actual, matcher)

HAMCREST_NS_END

#endif
