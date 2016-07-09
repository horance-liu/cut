#ifndef _35XQNLDP7FEDH3UBQW4Y4XL4X6NUNP13XRR3MLSJ7DBYTEI1VB1MAYIC               
#define _35XQNLDP7FEDH3UBQW4Y4XL4X6NUNP13XRR3MLSJ7DBYTEI1VB1MAYIC

#include <cum/internal/BaseMatcher.h>
#include <functional>

CUM_NS_BEGIN

template <typename T, typename F>
struct Comparator : BaseMatcher<T>
{
protected:
    Comparator
        ( const std::string& relationship
        , const T& expected)
        : relationship(relationship)
        , expected(expected)
    {}

private:
    __OVERRIDE__(void describeTo(Description& desc) const)
    {
        desc.appendText("a value ")
            .appendText(relationship)
            .appendText(" ")
            .appendValue(expected);
    }

    __OVERRIDE__(bool matches(const T& actual) const)
    {
        return functor(actual, expected);
    }

    __OVERRIDE__(void describeMismatch(const T& actual, Description& mismatch) const)
    {
        mismatch.appendValue(actual)
                .appendText(" ")
                .appendText(relationship)
                .appendText(" ")
                .appendValue(expected)
                .appendText(" got false");
    }

protected:
    const std::string relationship;
    const T expected;
    F functor;
};

CUM_NS_END

#endif
