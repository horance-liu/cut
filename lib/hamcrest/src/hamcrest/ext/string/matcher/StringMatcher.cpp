#include <hamcrest/ext/string/matcher/StringMatcher.h>
#include <ccinfra/algo/String.h>

HAMCREST_NS_BEGIN

inline std::string StringMatcher::converted(const std::string& str) const
{
    return ignoringCase ? ccinfra::to_lower(str) : str;
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

HAMCREST_NS_END
