//
// Terminal.cpp
//

#include <Arduino.h>

#include "Terminal.h"

#include "TaskScheduler.h"

void Terminal::begin(Stream& stream)
{
    _stream = &stream;

    if (!isRunning())
    {
        Scheduler.addTask(this);
    }
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

        if (c == 13)
        {
            if (_stream->peek() == 10)
            {
                _stream->read();
            }

            c = 10;
        }

        if (c == 8 || c == 127)
        {
            key = TerminalData::KeyDelete;
        }
        if (c == 10)
        {
            key = TerminalData::KeyEnter;
        }
        else if (c == 27)
        {
            key = TerminalData::KeyEscape;
        }
        else if (c >= 32 && c <= 126)
        {
            key = c;
        }

        if (_target != nullptr && key != TerminalData::Unknown)
        {
            const auto terminalData = TerminalData(key);

            _target->send<>(terminalData);
        }
    }

    task_leave
}
