#include <Arduino.h>

#include "TaskScheduler.h"

TaskScheduler Scheduler;

void TaskScheduler::tick(uint32_t msecs)
{
    auto timeoutData = TimeoutData(msecs);

    for (Task* task = _tasks.getFirst(), * prev = nullptr; task != nullptr; task = task->getNext())
    {
        if (task->isReadyToRun(msecs))
        {
            uint32_t start = millis();

            task->send<>(timeoutData);

            _taskMillis += millis() - start;
        }

        if (!task->isRunning())
        {
            task = _tasks.remove(task, prev);
        }
        else prev = task;
    }

    if ((uint16_t) millis() - _lastMillis > 5000)
    {
        //Serial << ((uint32_t) _taskMillis * 100) / 5000 << F("%") << endl;
        _cpuLoad = ((uint32_t) _taskMillis * 100) / 5000;

        _lastMillis = millis();
        _taskMillis = 0;
    }
}
