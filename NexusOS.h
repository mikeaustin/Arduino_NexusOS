//
// NexusOS.h
//

#ifndef NEXUSOS_H
#define NEXUSOS_H

template<typename T> inline Stream& operator <<(Stream& stream, const T value)
{
    stream.print(value);

    return stream;
}

inline Stream& operator <<(Stream& stream, Stream& (*function)(Stream&))
{
    return function(stream);
}

inline Stream& endl(Stream& stream)
{
    stream.println();

    return stream;
}

#include "utility/core/Stack.h"
#include "utility/Message.h"
#include "utility/Task.h"
#include "utility/TaskScheduler.h"
#include "utility/Terminal.h"
#include "utility/Shell.h"

#endif
