#ifndef H7E147A58_B997_4DC5_B6EB_A014CC6F6C3E
#define H7E147A58_B997_4DC5_B6EB_A014CC6F6C3E

#include <magellan/infra/std/SourceFile.h>
#include <magellan/framework/except/AssertionError.h>
#include <magellan/hamcrest/base/Matcher.h>
#include <magellan/hamcrest/base/Description.h>

MAGELLAN_NS_BEGIN

using HAMCREST_NS::Matcher;
using HAMCREST_NS::Description;
using HAMCREST_NS::Matcher;

template <typename U, typename V>
void assert_that(const U& actual, const Matcher<V>& matcher, const std::string& source)
{
    if (!matcher.matches(actual))
    {
        Description desc; 
        
        desc.appendText("\nExpected: ")
            .appendDescriptionOf(matcher)
            .appendText("\n     but: ");

        matcher.describeMismatch(actual, desc);

        throw AssertionError(source, desc.to_s());
    }
}

#define ASSERT_THAT(actual, matcher) \
    MAGELLAN_NS::assert_that(actual, matcher, FULL_FILE())

MAGELLAN_NS_END

#endif
