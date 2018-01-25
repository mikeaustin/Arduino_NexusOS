//
// TaskScheduler.h
//

#ifndef NEXUSOS_TASKSCHEDULER_H
#define NEXUSOS_TASKSCHEDULER_H

#include <NexusOS.h>

#include "core/List.h"
#include "Task.h"


struct TimeoutData {

    explicit TimeoutData(uint32_t msecs)
     : msecs(msecs)
    { }
  
    const uint32_t msecs;
  
};

//
// Sends TimeoutData messages to Tasks that have called yield() or sleep().
//

class TaskScheduler {

  public:
  
    void addTask(Task* task, Task* parent = nullptr)
    {
        _tasks.add(task);

        task->setParent(parent);
        task->run(Message(this));
    }

    void tick(uint32_t msecs)
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

    int numberOfTasks() const
    {
        int count = 0;

        for (Task* task = _tasks.getFirst(); task != nullptr; task = task->getNext())
        {
            ++count;
        }

        return count;
    }

    const List<Task> getTasks() const { return _tasks; }
    const int getCPULoad() const { return _cpuLoad; }

  private:

    List<Task> _tasks;

    uint16_t _taskMillis = 0;
    uint16_t _lastMillis = 0;

    int _cpuLoad = 0;
  
};


extern TaskScheduler Scheduler;

#endif
