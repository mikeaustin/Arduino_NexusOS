#include <NexusOS.h>

//
// This example shows how to define and create a task to blink an LED.
//

Stream& cout = Serial;

class Ping : public Task {

  public:

    Ping(Task* pong)
     : _pong(pong)
    { }

    bool run(const Message& message) override
    {
        task_enter
        
        cout << F("Ping") << endl;

        _pong->send(Message(10));

        task_leave
    }

  private:

    Task* _pong;

};

class Pong : public Task {

  public:

    bool run(const Message& message) override
    {
        task_enter

        task_sleep();

        if (const int* pingData = message.get<int>())
        {
            cout << F("Pong ") << *pingData << endl;        
        }
        
        task_leave
    }
  
};

Pong Pong;
Ping Ping(&Pong);

void setup()
{
    Serial.begin(9600);

    Scheduler.addTask(&Pong);
    Scheduler.addTask(&Ping);
}

void loop()
{
    Scheduler.tick(millis());
}
