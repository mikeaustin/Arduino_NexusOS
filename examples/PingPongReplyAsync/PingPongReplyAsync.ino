#include <NexusOS.h>

//
// This example shows how to define and create a task to blink an LED.
//

Stream& cout = Serial;

struct PingData {

    PingData(Task* sender = nullptr, int number = 0)
     : sender(sender),
       number(number)
    { }

    Task* sender;
    int   number;

};

class Ping : public Task {

  public:

    Ping(Task* pong)
     : _pong(pong)
    { }

    bool run(const Message& message) override
    {
        task_enter
        
        cout << F("Ping") << endl;

        auto pingData = PingData(this, 10);

        _pong->sendX<int>(pingData);

        _pong->send(Message(pingData));

        task_yield();

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

        if (auto pingData = message.get<PingData>())
        {
            _sender = pingData->sender;
            _value  = pingData->number;

            cout << F("Pong ") << pingData->number << endl;

            task_yield();

            _sender->send(Message(20));
        }
        
        task_leave
    }

  private:

    Task* _sender = nullptr;
    int   _value = 0;
  
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
