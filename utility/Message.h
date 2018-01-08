//
// Message.h
//

#ifndef NEXUSOS_MESSAGE_H
#define NEXUSOS_MESSAGE_H

#include <NexusOS.h>

template<typename T>
struct TypeInfo {
      
    static const void* GetType()
    {
        return reinterpret_cast<const void*>(&GetType);
    }
    
};


class Message {

  public:

    template<typename T>
    explicit Message(const T& data)
     : _type(TypeInfo<T>::GetType()),
       _data(&data)
    { }

    template<typename T>
    const T* get() const
    {
        if (TypeInfo<T>::GetType() == _type) {
            return static_cast<const T*>(_data);
        }

        return nullptr;
    }

  private:

    const void* _type = nullptr;
    const void* _data = nullptr;
  
};

#endif