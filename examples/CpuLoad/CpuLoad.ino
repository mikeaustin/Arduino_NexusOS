#include <NexusOS.h>

//
// This example shows how to get and print the CPU load.
//

class FullLoad : public Task {

  public:

    FullLoad()
     : Task(F("FullLoad"))
    { }

    bool run(const Message& message) override
    {
        task_enter

        for (;;)
        {
            // delay(1);

            task_sleep(0);
        }

        task_leave
    }

};

class PrintLoad : public Task {

  public:

    PrintLoad()
     : Task(F("PrintLoad"))
    { }

    bool run(const Message& message) override
    {
        task_enter

        for (;;)
        {
            task_sleep(1000);

            Serial << Scheduler.getCPULoad() << endl;;
        }

        task_leave
    }

};

FullLoad FullLoad;
PrintLoad PrintLoad;

void setup()
{
    Serial.begin(9600);

    Scheduler.addTask(&FullLoad);
    Scheduler.addTask(&PrintLoad);
}

void loop()
{
    Scheduler.tick(millis());
}
