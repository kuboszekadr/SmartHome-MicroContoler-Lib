#ifndef Services_h
#define Services_h

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <SPIFFS.h> // Include the SPIFFS library

#include <vector>

namespace Services
{
    class IService
    {
    public:
        IService();
        virtual void create() = 0;
    };

    class ISocket
    {
    public:
        ISocket();
    };

    extern AsyncWebServer server;

    extern std::vector<IService*> services;
    extern std::vector<AsyncWebSocket*> sockets;

    void init();
    void serveHTMLFolder();
}

#endif