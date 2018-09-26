#ifndef H7E147A58_B997_4DC5_B6EB_A014CC6F6C3E
#define H7E147A58_B997_4DC5_B6EB_A014CC6F6C3E

#include <cui/mem/__ScopeExit__.h>
#include <cui/utils/__SourceFile__.h>
#include <cum/base/Matcher.h>
#include <cum/base/Description.h>
#include <cut/except/AssertionError.h>

CUT_NS_BEGIN

#define FAIL(msg) throw AssertionError(__FULL_FILE__, msg);

template <typename E>
inline bool throwing(std::function<void()> f)
{
    try
    {
        f();
    } catch (const E& e) {
        return true;
    } catch (...) {
      FAIL("Expected exception to be thrown, but got different exception.");
      return false;
    }
    FAIL("Expected exception to be thrown, but got nothing.");
    return false;
}

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
    CUT_NS::assert_that(actual, matcher, __FULL_FILE__)

#define ASSERT_TRUE(actual) \
  ASSERT_THAT(actual, cum::be_true())

#define ASSERT_FALSE(actual) \
  ASSERT_THAT(actual, cum::be_false())

#define ASSERT_EQ(expected, actual) \
  ASSERT_THAT(actual, cum::eq(expected))

#define ASSERT_NE(expected, actual) \
  ASSERT_THAT(actual, cum::ne(expected))

#define ASSERT_LT(expected, actual) \
  ASSERT_THAT(actual, cum::lt(expected))

#define ASSERT_GT(expected, actual) \
  ASSERT_THAT(actual, cum::gt(expected))

#define ASSERT_LE(expected, actual) \
  ASSERT_THAT(actual, cum::le(expected))

#define ASSERT_GE(expected, actual) \
  ASSERT_THAT(actual, cum::ge(expected))

CUT_NS_END

#endif
