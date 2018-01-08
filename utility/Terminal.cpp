#include <Arduino.h>

#include "Terminal.h"
#include "TaskScheduler.h"


void Terminal::begin(Stream& stream)
{
    _stream = &stream;

    Scheduler.addTask(this);
}

bool Terminal::run(const Message& message)
{
    task_enter

    for (;;)
    {
        if (!_stream->available())
        {
            task_sleep(10);
        }

        int c = _stream->read();
        int key = TerminalData::Unknown;

        if (c == 10) continue;

        if (c == 13)
        {
            key = TerminalData::KeyEnter;
        }
        else if (c == 27)
        {
            key = TerminalData::KeyEscape;
        }
        else if (c >= 32 && c <= 127)
        {
            key = c;
        }

        if (_target != nullptr && key != TerminalData::Unknown)
        {
            const auto terminalData = TerminalData(key);
            
            _target->send(Message(terminalData));
        }
    }
    
    task_leave
}
