//
// Shell.h
//

#ifndef NEXUSOS_SHELL_H
#define NEXUSOS_SHELL_H

#include <NexusOS.h>

#include "core/Stack.h"
#include "Task.h"
#include "Terminal.h"

template<typename T>
class Array {

  public:

    Array()
     : _array(nullptr),
       _size(0)
    { }

    template<size_t S>
    Array(const T (&array)[S])
     : _array(array),
       _size(S)
    { }

    const T& operator [](size_t index) const
    {
        return _array[index];
    }

    size_t size() { return _size; }

  private:

    const T* _array;
    size_t   _size;

};

struct Command {

    __FlashStringHelper* name;
    void (*invoke)(Task* parent);

};

class Shell : public Task {

  public:

    Shell()
     : Task(F("Shell"))
    { }

    void begin(const Array<Command>& commands)
    {
        _commands = commands;
    }

    bool run(const Message& message) override;

  private:

    Stack<15, 1>   _buffer;
    Array<Command> _commands;
  
};

#endif
