#include <NexusOS.h>

//
// This example shows how to send messages to other tasks asynchronously.
//

Stream& cout = Serial;

struct PingData {

    PingData(Task* sender = nullptr, int value = 0)
     : sender(sender),
       value(value)
    { }

    Task* sender;
    int   value;

};

class Ping : public Task {

  public:

    Ping(Task* pong)
     : _pong(pong)
    { }

    bool run(const Message& message) override
    {
        task_enter

        auto pingData = PingData(this, 10);

        _pong->send(pingData);

        task_sleep();

        if (auto value = message.get<int>())
        {
            cout << F("Pong ") << *value << endl;
        }

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
            _pingData = *pingData;

            cout << F("Ping ") << _pingData.value << endl;

            task_yield();

            _pingData.sender->send(_pingData.value * 2);
        }

        task_leave
    }

  private:

    PingData _pingData;

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
