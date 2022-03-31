#ifndef StreamSerial__h
#define StreamSerial__h

#include <HardwareSerial.cpp>

namespace Streams
{
    void streamToSerial(const char *module_name,
                        const char *log_level,
                        const char *msg,
                        const char *timestamp)
    {
        char _msg[256];
        sprintf(_msg,
                "%s | %s | [%s] %s",
                module_name, log_level, timestamp, msg);
        Serial.println(_msg);
    }
}

#endif