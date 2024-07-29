#include "ServiceSystemTime.h"

void Services::ServiceSystemTime::create()
{
    server.on("/time", HTTP_GET, get);
}

void Services::ServiceSystemTime::get(AsyncWebServerRequest *request)
{
    String system_time = String(getTimestamp());

    JsonDocument doc;
    JsonObject result = doc.to<JsonObject>();
    result["time"] = system_time;

    char response[80];
    serializeJson(doc, response);

    request->send(
        200,
        "application/json",
        response);
}