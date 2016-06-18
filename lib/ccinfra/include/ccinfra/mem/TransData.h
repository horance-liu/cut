#ifndef CCINFRA_MEMORY_TRANS_DATA_H
#define CCINFRA_MEMORY_TRANS_DATA_H

#include "ccinfra/base/Status.h"
#include <ccinfra/base/Uncloneable.h>
#include "ccinfra/base/Assertions.h"

CCINFRA_NS_BEGIN

//
// Events:
// 1. update
// 2. modify
// 3. touch 
// 4. release
// 5. confirm
// 6. revert
// 7. reset
//
// States:
// 1. IDLE (valid=false, stable=true,  memoed=false, diff=false, cow=false)
//   1.1 update  -> NEW
//   1.2 modify  -> -
//   1.3 touch   -> IDLE
//   1.4 release -> IDLE
//   1.5 confirm -> IDLE
//   1.6 revert  -> IDLE
//   1.7 reset   -> IDLE

// 2. NEW  (valid=true,  stable=false, memoed=false, diff=false, cow=false)
//   1.1 update  -> NEW
//   1.2 modify  -> -
//   1.3 touch   -> NEW
//   1.4 release -> IDLE
//   1.5 confirm -> ACTIVE
//   1.6 revert  -> IDLE
//   1.7 reset   -> IDLE

// 3. ACTIVE (valid=true, stable=true, memoed=false, diff=false, cow=true)
//   1.1 update  -> MODIFIED
//   1.2 modify  -> MODIFIED
//   1.3 touch   -> TOUCHED
//   1.4 release -> RELEASED
//   1.5 confirm -> ACTIVE
//   1.6 revert  -> ACTIVE
//   1.7 reset   -> IDLE

// 4. MODIFIED (valid=true, stable=false, memoed=true, diff=true, cow=false)
//   1.1 update  -> MODIFIED
//   1.2 modify  -> -
//   1.3 touch   -> MODIFIED
//   1.4 release -> RELEASED
//   1.5 confirm -> ACTIVE
//   1.6 revert  -> ACTIVE
//   1.7 reset   -> IDLE

// 5. TOUCHED (valid=true, stable=false, memoed=false, diff=false, cow=true)
//   1.1 update  -> SHADOWED
//   1.2 modify  -> -
//   1.3 touch   -> TOUCHED
//   1.4 release -> RELEASED
//   1.5 confirm -> ACTIVE
//   1.6 revert  -> ACTIVE
//   1.7 reset   -> IDLE

// 6. SHADOWED(valid=true, stable=false, memoed=true, diff=false, cow=false)
//   1.1 update  -> SHADOWED
//   1.2 modify  -> -
//   1.3 touch   -> SHADOWED
//   1.4 release -> RELEASED
//   1.5 confirm -> ACTIVE
//   1.6 revert  -> ACTIVE
//   1.7 reset   -> IDLE

// 7. RELEASED(valid=false, stable=false, memoed=true, diff=false, cow=false)
//   1.1 update  -> SHADOWED
//   1.2 modify  -> -
//   1.3 touch   -> RELEASED
//   1.4 release -> RELEASED
//   1.5 confirm -> IDLE
//   1.6 revert  -> ACTIVE
//   1.7 reset   -> IDLE

template<typename T>
struct TransData
{
private:
    enum
    {
        TD_VALID  = 0x01,
        TD_STABLE = 0x02,
        TD_MEMOED = 0x04,
        TD_DIFF   = 0x08,
        TD_COW    = 0x10,
    };

    enum
    {
        IDLE     = TD_STABLE,
        ACTIVE   = TD_VALID  | TD_STABLE | TD_COW,
        NEW      = TD_VALID,
        MODIFIED = TD_VALID  | TD_MEMOED | TD_DIFF,
        TOUCHED  = TD_VALID  | TD_COW,
        SHADOWED = TD_VALID  | TD_MEMOED,
        RELEASED = TD_MEMOED,
    };

public:
   TransData() 
       : currentIndex(0)
       , state(IDLE)
   {
   }

   ~TransData()
   {
       reset();
   }

   bool isStable() const
   {
       return (state & TD_STABLE) > 0;
   }

   bool isPresent() const
   {
       return (state & TD_VALID) > 0;
   }

   bool isOldPresent() const
   {
       return (state & TD_MEMOED) > 0;
   }

   bool isNew() const
   {
       return state == NEW;
   }

   bool isChanged(bool restart = false) const
   {
       if(restart) return isPresent();
       if(isStable()) return false;

       if(state & TD_DIFF)
       {
           return getValue() != getOldValue();
       }

       return true;
   }

   T& getValue()
   {
       return getCurrentValue();
   }

   const T& getValue() const
   {
       return getCurrentValue();
   }

   T& getOldValue()
   {
       return getAnotherValue();
   }

   const T& getOldValue() const
   {
       return getAnotherValue();
   }

   T* operator->()
   {
       return const_cast<T*>(getPointer());
   }

   const T* operator->() const
   {
       return getPointer();
   }

   T& operator*()
   {
       return getValue();
   }

   const T& operator*() const
   {
       return getValue();
   }

   void revert()
   {
       if (isStable()) return;

       switch(state)
       {
       case NEW:
       case MODIFIED:
       case SHADOWED:
           freeCurrentValue();
           break;
       }

       if(state & TD_MEMOED)
       {
           switchCurrent();
       }

       state = (state == NEW ? IDLE : ACTIVE);
   }

   void confirm()
   {
       if (!isStable())
       {
           freeOldValue();
           state = (state == RELEASED ? IDLE : ACTIVE);
       }
   }

   void forceUpdate()
   {
       backup();
       prepareForUpdate();
   }

   void update(const T& value)
   {
       forceUpdate();
       getCurrentValue() = value;
   }

   Status modify()
   {
        CCINFRA_ASSERT_TRUE(ACTIVE == state);

        CCINFRA_ASSERT_SUCC_CALL(getCurrentValue().copyTo(getAnotherValue()));

        state = MODIFIED;

        return CCINFRA_SUCCESS;
   }

   void touch()
   {
       if(state == ACTIVE)
       {
           state = TOUCHED;
       }
   }

   void release()
   {
       backup();

       switch(state)
       {
       case IDLE:
       case NEW:
           state = IDLE; break;
       default:
           state = RELEASED; break;
       }
   }

   void reset()
   {
       freeOldValue();
       freeCurrentValue();
       state = IDLE;
   }

   unsigned char getIndex() const
   {
       return currentIndex;
   }

   unsigned char getState() const
   {
       return state;
   }

private:

    void freeOldValue()
    {
        if(isOldPresent())
        {
            getAnotherValue().reset();
        }
    }

    void freeCurrentValue()
    {
        if(isPresent())
        {
            getCurrentValue().reset();
        }
    }

    void backup()
    {
        if(state & TD_COW)
        {
            switchCurrent();
        }
    }

    const T* getPointer() const
    {
        return isPresent() ? &getCurrentValue() : 0;
    }

    void prepareForUpdate()
    {
        switch(state)
        {
        case IDLE:     state = NEW;      break;
        case RELEASED: state = SHADOWED; break;
        case ACTIVE:   state = MODIFIED; break;
        case TOUCHED:  state = SHADOWED; break;
        default:
            break;
        }
    }

   void switchCurrent()
   {
       currentIndex = getAnotherIndex();
   }

   unsigned char getAnotherIndex() const
   {
       return 1 - currentIndex;
   }

   const T& getCurrentValue() const
   {
       return values[currentIndex];
   }

   T& getCurrentValue()
   {
       return values[currentIndex];
   }

   const T& getAnotherValue() const
   {
       return values[getAnotherIndex()];
   }

   T& getAnotherValue()
   {
       return values[getAnotherIndex()];
   }

private:
    T values[2];
    unsigned char currentIndex :1;
    unsigned char state:5;

    DISALLOW_COPY(TransData);
};

#define __trans_data(p_type, p_name)  TransData< p_type > p_name

CCINFRA_NS_END

#endif

