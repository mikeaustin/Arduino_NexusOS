#include <NexusOS.h>

//
// This example shows how to define and create a task to blink an LED more
// precicely. It eliminates time 'drift' by getting the next wall-clock second.
//

class Blink : public Task {

  public:

    bool run(const Message& message) override
    {
        task_enter

        pinMode(13, OUTPUT);

        task_yield();

        for (;;)
        {
            if (auto timeoutData = message.get<TimeoutData>())
            {
                digitalWrite(13, HIGH);
                task_sleep(timeoutData->msecs / 500 * 500 + 500 - timeoutData->msecs);
            }

            if (auto timeoutData = message.get<TimeoutData>())
            {
                digitalWrite(13, LOW);
                task_sleep(timeoutData->msecs / 500 * 500 + 500 - timeoutData->msecs);
            }
        }

        task_leave
    }

};

Blink Blink;

void setup()
{
    Serial.begin(9600);

    Scheduler.addTask(&Blink);
}

void loop()
{
    Scheduler.tick(millis());
}
