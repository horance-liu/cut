#include <hamcrest/core/SubstringMatcher.h>

HAMCREST_NS_BEGIN

SubstringMatcher::SubstringMatcher
    ( const std::string& relationship
    , const std::string& substring
    , const bool ignoringCase)
    : relationship(relationship)
    , substring(substring)
    , ignoringCase(ignoringCase)
{
}

namespace
{
    std::string toLowerCase(std::string str)
    {
        for (auto &c : str)
        {
            c = std::tolower(c);
        }

        return str;
    }
}

bool SubstringMatcher::matches(const std::string& actual) const
{
    return evalSubstringOf(ignoringCase ? toLowerCase(actual) : actual);
}

void SubstringMatcher::describeTo(Description& description) const
{
    description.appendText("a string ")
            .appendText(relationship)
            .appendText(" ")
            .appendValue(substring);

    if (ignoringCase)
    {
        description.appendText(" ignoring case");
    }
}

void SubstringMatcher::describeMismatch
    (const std::string& item, Description& mismatch) const
{
    mismatch.appendText("was \"").appendText(item).appendText("\"");
}

std::string SubstringMatcher::converted(const std::string& str) const
{
    return ignoringCase ? toLowerCase(str) : str;
}

HAMCREST_NS_END
