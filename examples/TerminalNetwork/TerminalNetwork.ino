#include <NexusOS.h>

#include <Ethernet.h>


//
// This example shows how to define a simple task to echo terminal input.
//

class xClient : public Task {

  public:

    bool run(const Message& message) override
    {
        Stream& cout = getStream();

        task_enter

        cout << F("Type something. Keys are echoed back to you.") << endl;

        cout << F("] ");

        for (;;)
        {
            task_sleep();

            if (auto terminalData = message.get<TerminalData>())
            {
                switch (terminalData->key)
                {
                    case TerminalData::KeyEnter:
                        cout << endl << F("] "); break;
                    default:
                        cout << (char) terminalData->key;
                }
            }
        }
        
        task_leave
    }
  
};


Terminal Console;
xClient xClient;

byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168, 0, 177);

EthernetServer Server(23);
EthernetClient Client;

void setup()
{
    Serial.begin(9600);

    Ethernet.begin(mac, ip);
    Server.begin();
}

void loop()
{
    EthernetClient client = Server.available();

    if (client && client.peek() == 27)
    {
        client.stop();

        Client = EthernetClient();

        xClient.exit();
    }

    if (client && client != Client)
    {
        Console.begin(client);
        Console.setTarget(&xClient);

        Scheduler.addTask(&xClient, &Console);

        Client = client;
    }

    // if (client && client.available() > 0)
    // {
    //     client << client.read();
    // }

    Scheduler.tick(millis());
}
