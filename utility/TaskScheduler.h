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
                task->send<>(timeoutData);
            }

            if (!task->isRunning())
            {
                task = _tasks.remove(task, prev);
            }
            else prev = task;
        }
    }

    int numberOfTasks()
    {
        int count = 0;

        for (Task* task = _tasks.getFirst(); task != nullptr; task = task->getNext())
        {
            ++count;
        }

        return count;
    }

  private:

    List<Task> _tasks;
  
};


extern TaskScheduler Scheduler;

#endif
