#ifndef H4CF77BF5_F4CD_4EA0_97AB_28949E22B433
#define H4CF77BF5_F4CD_4EA0_97AB_28949E22B433

#include <hamcrest/internal/BaseMatcher.h>
#include <algorithm>
#include <vector>

HAMCREST_NS_BEGIN

template <typename C, typename T>
struct IsIn : BaseMatcher<T>
{
    IsIn(const C& c)
        : container(c)
    {}

    template <class InputIterator>
    IsIn(InputIterator first, InputIterator last)
        : container(first, last)
    {}

    explicit IsIn(std::initializer_list<T> list)
        : container(list)
    {}

    virtual ~IsIn() = default;

private:
    OVERRIDE(const Matcher<T>* clone() const)
    {
        return new IsIn(container);
    }

    OVERRIDE(bool matches(const T& actual) const)
    {
        return std::find(begin(container), end(container), actual)
            != end(container);
    }

    OVERRIDE(void describeTo(Description& desc) const)
    {
        desc.appendText("one of ")
            .appendValueList("{", ", ", "}", container);
    }

private:
    const C container;
};

template <typename C, typename T>
struct MatcherTraits<IsIn<C, T>>
{
    using argument = T;
    using category = MatcherTag;
};

HAMCREST_NS_END

#endif
