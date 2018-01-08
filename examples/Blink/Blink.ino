#include <NexusOS.h>

//
// This example shows how to define and create a task to blink an LED.
//

class Blink : public Task {

  public:

    bool run(const Message& message) override
    {
        task_enter

        pinMode(13, OUTPUT);

        for (;;)
        {
            digitalWrite(13, HIGH);
            task_sleep(500);
        
            digitalWrite(13, LOW);
            task_sleep(500);
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
