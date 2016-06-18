#ifndef CCINFRA_STRUCT_WRAPPER__H__
#define CCINFRA_STRUCT_WRAPPER__H__

#include <ccinfra/ccinfra.h>
#include <ccinfra/base/StaticAssert.h>

CCINFRA_NS_BEGIN

template <typename FROM, typename TO>
struct StructWrapper : FROM
{
	static const TO& by(const FROM& from)
	{
	    STATIC_ASSERT(sizeof(FROM) == sizeof(TO));

	    return (const TO&)from;
	}

	static TO& by(FROM& from)
	{
		return (TO&)from;
	}
};

#define STRUCT_WRAPPER(to, from) struct to : StructWrapper<from, to>

CCINFRA_NS_END

#endif 
