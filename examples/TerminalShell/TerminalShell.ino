#include <NexusOS.h>

//
// This example shows how to define shell command and respond to them.
//

const char tasks_name[] PROGMEM = "tasks";

void tasks_invoke(Task* parent)
{
    Stream& cout = parent->getStream();

    cout << F("here") << endl;
}

const Command Commands[] PROGMEM =
{
    (__FlashStringHelper*) tasks_name,
    tasks_invoke
};

Terminal Console;
Shell Shell;

void setup()
{
    Serial.begin(9600);

    Console.begin(Serial);
    Console.setTarget(&Shell);

    Shell.begin(Commands);

    Serial << F("NexusOS 0.1.0 | 2018 Mike Austin") << endl;

    Scheduler.addTask(&Shell, &Console);
}

void loop()
{
    Scheduler.tick(millis());
}
