#ifndef ServiceSerial_h
#define ServiceSerial_h

#include "Services/Services.h"
#include <vector>

#include <ArduinoJson.h>
#include <AsyncJson.h>

namespace Services
{
    class ServiceSerial : public IService
    {
    public:
        void create();

        static void newEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    };

}

extern AsyncWebSocket serial_socket;
extern std::vector<String> logs_buffer;

#endif