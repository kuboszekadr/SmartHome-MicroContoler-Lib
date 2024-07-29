#ifndef LoggerOnlineSerial
#define LoggerOnlineSerial

#include <Arduino.h>
#include <vector>
#include <ArduinoJson.h>
#include <AsyncWebSocket.h> 
#include <AsyncJson.h>

extern AsyncWebSocket serial_socket;
std::vector<String> logs_buffer; 

namespace Loggers {
    void logToWebSerial(const char *module_name,
                const char *log_level,
                const char *msg,
                const char *timestamp)
    {
        JsonDocument doc;

        doc["module_name"] = module_name;
        doc["log_level"] = log_level;
        doc["msg"] = msg;
        doc["timestamp"] = timestamp;

        String json;
        serializeJson(doc, json);        

        serial_socket.textAll(json);

        if (logs_buffer.size() >= 10) {
            logs_buffer.erase(logs_buffer.begin());
        }
        logs_buffer.push_back(json);
    }
}

#endif