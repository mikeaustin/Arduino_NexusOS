#include <NexusOS.h>


//
// This example shows how to define a simple task to echo terminal input.
//

class Client : public Task {

  public:

    bool run(const Message& message) override
    {
        Stream& cout = getStream();

        task_enter

        for (;;)
        {
            task_sleep();

            if (auto terminalData = message.get<TerminalData>())
            {
                switch (terminalData->key)
                {
                    case TerminalData::KeyEnter:
                        cout << endl; break;
                    default:
                        cout << (char) terminalData->key;
                }
            }
        }
        
        task_leave
    }
  
};


Terminal Console;
Client Client;

void setup()
{
    Serial.begin(9600);

    Console.begin(Serial);
    Console.setTarget(&Client);

    Scheduler.addTask(&Client, &Console);
}

void loop()
{
    Scheduler.tick(millis());
}
