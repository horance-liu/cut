#ifndef CCINFRA_STRUCT_OBJECT_H
#define CCINFRA_STRUCT_OBJECT_H

#include <ccinfra/ccinfra.h>
#include <string.h>

CCINFRA_NS_BEGIN

template <typename OBJ>
struct StructObject : OBJ
{
	StructObject()
	{
		reset();
	}

	void reset()
	{
		::memset((void*)this, 0x00, sizeof(OBJ));
	}

	OBJ& operator*()
    {
        return *this;
    }

    const OBJ& operator*() const
    {
        return *this;
    }

    OBJ* operator->()
    {
        return this;
    }

    const OBJ* operator->() const
    {
        return this;
    }

    OBJ* getPointer()
    {
        return this;
    }

    const OBJ* getPointer() const
    {
        return this;
    }
};

CCINFRA_NS_END

#endif

