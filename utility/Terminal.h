//
// Terminal.h
//

#ifndef NEXUSOS_TERMINAL_H
#define NEXUSOS_TERMINAL_H

#include <NexusOS.h>

#include "Task.h"


struct TerminalData {

    enum Key
    {
        Unknown = 0,
        KeyDelete = 8,
        KeyEnter = 10,
        KeyEscape = 27
    };

    TerminalData(int key)
     : control(key < 32 || key == 127),
       key(key)
    { }

    const bool control;
    const int  key;
  
};

//
// Translates stream characters into key codes and sends to them to target.
//

class Terminal : public Task {

  public:

    Terminal()
     : Task(F("Terminal"))
    { }

    virtual Stream& getStream() const { return *_stream; }

    void setTarget(Task* target) { _target = target; }

    void begin(Stream& stream);
  
    bool run(const Message& message) override;

  private:

    Stream* _stream = nullptr;
    Task*   _target = nullptr;

};

#endif
