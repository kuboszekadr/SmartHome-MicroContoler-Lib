#ifndef ServiceRestart_h
#define ServiceRestart_h

#include "Serices/Services.h"
#include "Config/Config.h"

#include <ArduinoJson.h>
#include <AsyncJson.h>

namespace Services
{
    class ServiceRestart : public IService
    {
    public:
        void create();

        static void get(AsyncWebServerRequest *request);
    };

    extern ServiceRestart restart;
}

#endif