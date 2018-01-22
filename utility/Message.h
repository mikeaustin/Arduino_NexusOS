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
    
    void Archive(Stream& stream, const T& value) { }
};

template<>
inline void TypeInfo<int>::Archive(Stream& stream, const int& value)
{
    stream << value;
}


class Result {

  public:

    explicit Result() { }

    template<typename T>
    explicit Result(T& data)
     : _type(TypeInfo<T>::GetType()),
       _data(&data)
    { }

    template<typename T>
    Result& operator =(const T& data)
    {
        if (TypeInfo<T>::GetType() == _type)
        {
            *static_cast<T* const>(_data) = data;
        }

        return *this;
    }

  private:

    const void* const _type = nullptr;
    void* const _data = nullptr;
  
};

class Message {

  public:

    template<typename T>
    explicit Message(const T& data, Result&& result = Result())
     : result(result),
       _type(TypeInfo<T>::GetType()),
       _data(&data)
    { }

    template<typename T>
    const T* get() const
    {
        if (TypeInfo<T>::GetType() == _type)
        {
            return static_cast<const T* const>(_data);
        }

        return nullptr;
    }

    Result& result;

  private:

    const void* const _type = nullptr;
    const void* const _data = nullptr;

};

#endif
