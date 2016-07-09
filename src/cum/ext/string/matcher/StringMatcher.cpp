#include <cum/ext/string/matcher/StringMatcher.h>
#include <cui/algo/__string__.h>

CUM_NS_BEGIN

inline std::string StringMatcher::converted(const std::string& str) const
{
    return ignoringCase ? cui::to_lower(str) : str;
}

StringMatcher::StringMatcher
    ( bool ignoringCase
    , const std::string& relationship
    , const std::string& substring)
    : ignoringCase(ignoringCase)
    , relationship(relationship)
    , expected(converted(substring))
{
}

bool StringMatcher::matches(const std::string& actual) const
{
    return evalOf(converted(actual));
}

void StringMatcher::describeTo(Description& description) const
{
    description.appendText("a string ")
            .appendText(relationship + " ")
            .appendValue(expected);

    if (ignoringCase)
    {
        description.appendText(" ignoring case");
    }
}

void StringMatcher::describeMismatch
    (const std::string& item, Description& mismatch) const
{
    mismatch.appendText("was \"").appendText(item).appendText("\"");
}

CUM_NS_END
