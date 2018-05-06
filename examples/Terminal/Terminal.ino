#include <NexusOS.h>

//
// This example shows how to define a simple task to echo terminal input.
//

class Echo : public Task {

  public:

    bool run(const Message& message) override
    {
        Stream& cout = getStream();

        task_enter

        cout << F("Type stuff. Characters are echoed back to you.") << endl;

        for (;;)
        {
            task_sleep();

            if (auto terminalData = message.get<TerminalData>())
            {
                if (terminalData->control)
                {
                    switch (terminalData->key)
                    {
                        case TerminalData::KeyEnter: {
                            cout << endl; break;
                        }
                    }
                }
                else cout << (char) terminalData->key;
            }
        }

        task_leave
    }

};

Terminal Console;
Echo Echo;

void setup()
{
    Serial.begin(9600);

    Console.begin(Serial);
    Console.setTarget(&Echo);

    Scheduler.addTask(&Echo, &Console);
}

void loop()
{
    Scheduler.tick(millis());
}
