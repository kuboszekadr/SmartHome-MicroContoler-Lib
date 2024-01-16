#ifndef TimeService_h
#define TimeService_h

#include "Serices/Services.h"

#include <ESP32Time.h>

namespace Services
{
    class ServiceSystemTime : public IService
    {
    public:
        void create();
        static void get(AsyncWebServerRequest *request);
    };

    extern ServiceSystemTime time;
}



#endif