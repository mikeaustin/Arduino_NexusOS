//
// Shell.cpp
//

#include <Arduino.h>

#include "Shell.h"

#include "Terminal.h"

bool Shell::run(const Message& message)
{
    Stream& cout = getStream();

    task_enter

    cout << F("] ");

    for (;;)
    {
        task_sleep();

        if (auto terminalData = message.get<TerminalData>())
        {
            if (terminalData->control)
            {
                switch (terminalData->key)
                {
                    case TerminalData::KeyDelete:
                    {
                        if (_buffer.pop())
                        {
                            cout << F("\b \b");
                        }
                    }
                    break;
                    case TerminalData::KeyEnter:
                    {
                        cout << endl;

                        if (_buffer.size() > 0)
                        {
                            _buffer[_buffer.size()] = '\0';

                            Command command;

                            for (size_t i = 0; i < _commands.size(); i++)
                            {
                                memcpy_P(&command, &_commands[0], sizeof(Command));

                                if (strcmp_P(&_buffer[0], (const char*) command.name) == 0)
                                {
                                    command.invoke(this);
                                }
                            }

                            _buffer.reset();
                        }

                        cout << F("] ");
                    }
                    break;
                }
            }
            else
            {
                if (_buffer.push(terminalData->key))
                {
                    cout << (char) terminalData->key;
                }
            }
        }
    }

    task_leave
}
