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

    void tick(uint32_t msecs);

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
