#ifndef H0CBC1D58_7346_4567_B281_358825C0504E
#define H0CBC1D58_7346_4567_B281_358825C0504E

#include <ccinfra/base/BaseTypes.h>
#include <ccinfra/base/EqHelper.h>

CCINFRA_NS_BEGIN

template <typename VALUE_TYPE, VALUE_TYPE MAX_VALUE>
struct RingNumber
{
	RingNumber(const U64 value = 0) : value(value % MAX_VALUE) {}

	RingNumber& operator=(const RingNumber& another)
	{
		value = another.value;
		return *this;
	}

    __INLINE_EQUALS(RingNumber)
    {
		return __FIELD_EQ(value);
    }


	VALUE_TYPE operator>>(const VALUE_TYPE offset) const
	{
		return (value + offset) % MAX_VALUE;
	}

	VALUE_TYPE operator<<(const VALUE_TYPE offset) const
	{
		return (value + MAX_VALUE - offset) % MAX_VALUE;
	}

	RingNumber& operator>>=(const VALUE_TYPE offset)
	{
		value = *this >> offset;
		return *this;
	}

	RingNumber& operator<<=(const VALUE_TYPE offset)
	{
		value = *this << offset;
		return *this;
	}

    RingNumber& operator++()
    {
        *this >>= 1;
        return *this;
    }

    RingNumber operator++(int)
    {
        VALUE_TYPE oldValue = value;
        *this >>= 1;
        return RingNumber(oldValue);
    }

    RingNumber& operator--()
    {
        *this <<= 1;
        return *this;
    }

    RingNumber operator--(int)
    {
        VALUE_TYPE oldValue = value;
        *this <<= 1;
        return RingNumber(oldValue);
    }

	VALUE_TYPE operator*() const
	{
		return value;
	}

    VALUE_TYPE operator-(const RingNumber& rhs) const
    {
    	return *this << *rhs;
    }

private:
	VALUE_TYPE value;
};

CCINFRA_NS_END

#endif
