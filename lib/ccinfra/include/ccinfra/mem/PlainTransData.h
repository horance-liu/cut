#ifndef CCINFRA_MEMORY_PLAIN_TRANS_DATA_H
#define CCINFRA_MEMORY_PLAIN_TRANS_DATA_H

#include <ccinfra/mem/TransData.h>
#include <memory.h>

CCINFRA_NS_BEGIN

template <typename T>
struct PlainObject
{
   PlainObject() { reset(); }

   PlainObject(const T& object) : object(object) {}

   PlainObject& operator=(const PlainObject& rhs)
   {
      object = rhs.object;
      return *this;
   }

   bool operator==(const PlainObject& rhs) const
   {
      return object == rhs.object;
   }

   bool operator!=(const PlainObject& rhs) const
   {
       return object != rhs.object;
   }

   void reset()
   {
       //object.~T();
   }

   Status copyTo(PlainObject& rhs)
   {
      ::memcpy((void*)&(rhs.object), (void*)&object, sizeof(object));
      return CCINFRA_SUCCESS;
   }

   T* getObject()
   {
      return &object;
   }

   const T* getObject() const
   {
      return &object;
   }

private:
   T object;
};

template <typename T>
struct PlainTransData
{
   PlainTransData() {}

   void revert()
   {
      data.revert();
   }

   void confirm()
   {
      data.confirm();
   }

   void update(const T& value)
   {
      data.update(value);
   }

   void forceUpdate()
   {
       data.forceUpdate();
   }

   Status modify()
   {
      return data.modify();
   }

   void touch()
   {
       data.touch();
   }

   void release()
   {
       data.release();
   }

   void reset()
   {
      data.reset();
   }

   bool isPresent() const
   {
       return data.isPresent();
   }

   bool isStable() const
   {
      return data.isStable();
   }

   T* operator->()
   {
      return const_cast<T*>(getObject());
   }

   const T* operator->() const
   {
      return getObject();
   }

   T& operator*()
   {
      return *(operator->());
   }

   const T& operator*() const
   {
      return *(operator->());
   }

   bool isOldPresent() const
   {
      return data.isOldPresent();
   }

   const T& getOldValue() const
   {
      return *(data.getOldValue().getObject());
   }

   const T& getValue() const
   {
       return *(getObject());
   }

   bool isChanged(bool restart = false) const
   {
       return data.isChanged(restart);
   }

private:
   const T* getObject() const
   {
      const PlainObject<T>* object = data.operator->();
      return object == 0 ? 0 : object->getObject();
   }

private:
   PlainTransData(const PlainTransData&);

private:
   TransData<PlainObject<T> > data;
};

#define __plain_trans_data(type, name)  PlainTransData< type > name

CCINFRA_NS_END

#endif

