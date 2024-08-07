#ifndef SmartHomeDevice__h
#define SmartHomeDevice__h

#include "Logger/Logger.h"

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

class SmartHomeDevice
{
    public:
        SmartHomeDevice(const char *host, int port, String device_name);
        ~SmartHomeDevice() {};

        void setupAPI(bool is_enabled=true) {_api_enabled = is_enabled;}

        bool sync(JsonDocument &doc);
        
        int postData(const JsonVariant &obj, const char *endpoint);
        String getData(const JsonVariant &obj, const char *endpoint, const char *version);

        void postReadings(const JsonVariant &obj, const char *sensor_name);
        void postLog(const JsonVariant &obj);
        void postNotification(const char *title, const char *message);

        char host_url[32];
        char device_name[32];
    protected:
        Logger logger = Logger("SmartHomeDevice");
        char _host[20];
        char _url[5];

        bool _api_enabled = true;
};

#endif
