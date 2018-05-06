#include <NexusOS.h>

//
// This example shows how to define and create a task to blink an LED, then
// exiting after 5 iterations. Use member variables to persist state.
//

class Blink : public Task {

  public:

    bool run(const Message& message) override
    {
        task_enter

        pinMode(13, OUTPUT);

        for (i = 0; i < 5; i++)
        {
            digitalWrite(13, HIGH);
            task_sleep(500);

            digitalWrite(13, LOW);
            task_sleep(500);
        }

        task_leave
    }

  private:

    int i = 0;

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
