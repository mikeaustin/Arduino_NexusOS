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
        Unknown = 0, KeyEnter = 10, KeyEscape = 27
    };

    TerminalData(int key)
     : key(key)
    { }

    const int key;
  
};

//
// Translates stream characters into key codes and sends to them to target.
//

class Terminal : public Task {

  public:

    virtual Stream& getStream() const { return *_stream; }

    void setTarget(Task* target) { _target = target; }

    void begin(Stream& stream);
  
    bool run(const Message& message) override;

  private:

    Stream* _stream = nullptr;
    Task*   _target = nullptr;

};

#endif
