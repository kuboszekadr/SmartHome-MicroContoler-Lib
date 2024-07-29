#ifndef TimeService_h
#define TimeService_h

#include "Services/Services.h"
#include "Timestamp/Timestamp.h"

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