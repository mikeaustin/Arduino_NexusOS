#include <NexusOS.h>

//
// This example shows how to send messages to other tasks.
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

        int pongData = _pong->send<int>(10);

        cout << F("Pong ") << pongData << endl;

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

        if (auto pingData = message.get<int>())
        {
            cout << F("Ping ") << *pingData << endl;

            message.result = *pingData * 2;
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
