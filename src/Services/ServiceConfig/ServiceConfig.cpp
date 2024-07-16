#include "ServiceConfig.h"

void Services::ServiceConfig::create()
{
    AsyncCallbackJsonWebHandler *get_handler = new AsyncCallbackJsonWebHandler(
        "/config",
        get);
    get_handler->setMethod(HTTP_GET);
    server.addHandler(get_handler);

    AsyncCallbackJsonWebHandler *post_handler = new AsyncCallbackJsonWebHandler(
        "/config",
        post);
    post_handler->setMethod(HTTP_POST);
    server.addHandler(post_handler);
}

void Services::ServiceConfig::get(AsyncWebServerRequest *request, JsonVariant &json)
{
    JsonObject obj = json.as<JsonObject>();
    
    const char* file = obj["file_name"];
    const char* folder = obj["folder"] | "config";

    Config config = Config(file, folder);
    config.load();

    String response;
    serializeJson(config.data, response);
    Serial.println(response);
    
    request->send(
        200,
        "application/json",
        response);
}

void Services::ServiceConfig::post(AsyncWebServerRequest *request, JsonVariant &json)
{
    JsonObject obj = json.as<JsonObject>();

    const char* file = obj["file_name"];
    const char* folder = obj["folder"] | "config";
    
    Config config = Config(file, folder);
    config.data = obj["content"];

    int status = config.save();
    if (status != CONFIG_SAVED)
    {
        request->send(500);
    }

    config.load();
    JsonDocument response_obj;
    response_obj["status"] = "ok";
    response_obj["content"] = config.data;

    AsyncResponseStream *response = request->beginResponseStream("application/json");
    serializeJson(response_obj, *response);
    request->send(response);    
}

