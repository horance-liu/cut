#ifndef _35XQNLDP7FEDH3UBQW4Y4XL4X6NUNP13XRR3MLSJ7DBYTEI1VB1MAYIC               
#define _35XQNLDP7FEDH3UBQW4Y4XL4X6NUNP13XRR3MLSJ7DBYTEI1VB1MAYIC

#include <magellan/hamcrest/internal/BaseMatcher.h>

HAMCREST_NS_BEGIN

template <typename T>
struct Comparator : BaseMatcher<T>
{
protected:
    Comparator(const std::string& relationship, const T& expected) 
        : relationship(relationship), expected(expected)
    {}

private:
    OVERRIDE(void describeTo(Description& desc) const)
    {
        desc.appendText("a value ")
            .appendText(relationship)
            .appendText(" ")
            .appendValue(expected);
    }

protected:
    const std::string relationship;
    const T expected;
};

HAMCREST_NS_END

#endif
