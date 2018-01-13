//
// Task.h
//

#ifndef NEXUSOS_TASK_H
#define NEXUSOS_TASK_H

#include <NexusOS.h>

#include "core/List.h"
#include "Message.h"

#define MERGE_LINE(line) LABEL_##line
#define LABEL_LINE(line) MERGE_LINE(line)

#define task_enter      if (_context) goto *_context;
#define task_yield(...) _yield(&&LABEL_LINE(__LINE__), ##__VA_ARGS__); return false; LABEL_LINE(__LINE__):
#define task_sleep(...) _sleep(&&LABEL_LINE(__LINE__), ##__VA_ARGS__); return false; LABEL_LINE(__LINE__):
#define task_leave      _context = nullptr; return true;

//
// A cooperative-thread that can yield immediately or sleep for msecs seconds.
//

class Task : public List<Task>::Node {

  public:

    Task() { }

    virtual Stream& getStream() const
    {
        return _parent->getStream();
    }

    void setParent(Task* parent)
    {
        _parent = parent;
    }

    template<typename R = nullptr_t, typename T>
    R send(const T& data)
    {
        R value;

        if (isRunning())
        {
            run(Message(data, Result(value)));
        }

        return value;
    }

    bool isRunning()
    {
        return _context != nullptr;
    }

    bool isReadyToRun(uint32_t msecs)
    {
        return msecs - _abstime >= _timeout;
    }

    virtual bool run(const Message& message)
    {
        return false;
    }

    void _yield(void* context)
    {
        _context = context;
    }

    void _sleep(void* context, uint32_t msecs = UINT32_MAX)
    {
        _abstime = millis();
        _timeout = msecs;

        _yield(context);
    }

  protected:

    void*    _context = nullptr;
    Task*    _parent = nullptr;

    uint32_t _abstime = 0;
    uint32_t _timeout = 0;

};

#endif
