#ifndef HCD10D15E_02AF_44EE_B349_E56C07B93A5A
#define HCD10D15E_02AF_44EE_B349_E56C07B93A5A

#include <cum/internal/SelfDescribingValue.h>
#include <vector>

CUM_NS_BEGIN

template <typename C>
struct SelfDescribingContainer
{
    using value_type = SelfDescribingValue<typename C::value_type>;
    using iterator = typename std::vector<value_type>::iterator;
    using const_iterator = typename std::vector<value_type>::const_iterator;

    explicit SelfDescribingContainer(const C& c)
    {
        for(auto i = std::begin(c); i != std::end(c); ++i)
        {
            values.emplace_back(*i);
        }
    }

    const_iterator begin() const
    { return values.begin(); }

    const_iterator end() const
    { return values.end(); }

    iterator begin()
    { return values.begin(); }

    iterator end()
    { return values.end(); }

private:
    std::vector<value_type> values;
};

CUM_NS_END

#endif
