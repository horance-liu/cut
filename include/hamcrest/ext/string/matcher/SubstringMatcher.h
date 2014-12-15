#ifndef H4F7A9E79_EF75_4EEE_BA1E_F5C16CF3DD3D
#define H4F7A9E79_EF75_4EEE_BA1E_F5C16CF3DD3D

#include <hamcrest/internal/BaseMatcher.h>

HAMCREST_NS_BEGIN

struct SubstringMatcher : BaseMatcher<std::string>
{
protected:
    SubstringMatcher
        ( const std::string& relationship
        , const std::string& substring
        , const bool ignoringCase);

private:
    OVERRIDE(bool matches(const std::string& actual) const);
    OVERRIDE(void describeTo(Description& desc) const);
    OVERRIDE(void describeMismatch(const std::string&, Description&) const);

protected:
    std::string converted(const std::string& string) const;

private:
    ABSTRACT(bool evalSubstringOf(const std::string&) const);

protected:
    const std::string relationship;
    const std::string substring;
    const bool ignoringCase;
};

HAMCREST_NS_END

#endif
