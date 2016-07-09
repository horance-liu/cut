#ifndef H7E147A58_B997_4DC5_B6EB_A014CC6F6C3E
#define H7E147A58_B997_4DC5_B6EB_A014CC6F6C3E

#include <cui/mem/__ScopeExit__.h>
#include <cui/utils/__SourceFile__.h>
#include <cum/base/Matcher.h>
#include <cum/base/Description.h>
#include <cut/except/AssertionError.h>

CUT_NS_BEGIN

template <typename U, typename V>
void assert_that(const U& actual, cum::Matcher<V>* matcher, const std::string& source)
{
    __SCOPE_EXIT__([=]{ delete matcher; });

    if (!matcher->matches(static_cast<V>(actual)))
    {
        cum::Description desc;
        
        desc.appendText("\nExpected: ")
            .appendDescriptionOf(*matcher)
            .appendText("\n     but: ");

        matcher->describeMismatch(static_cast<V>(actual), desc);

        throw AssertionError(source, desc.to_s());
    }
}

#define ASSERT_THAT(actual, matcher) \
    CUT_NS::assert_that(actual, matcher, __FULL_FILE__())

CUT_NS_END

#endif
