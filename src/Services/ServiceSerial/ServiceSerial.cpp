#include "ServiceSerial.h"

void Services::ServiceSerial::create()
{
    serial_socket.onEvent(newEvent);
}

void Services::ServiceSerial::newEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    Serial.println(type);
    switch (type)
    {
    case WS_EVT_CONNECT:
        Serial.printf(
            "WebSocket client #%u connected from %s\n",
            client->id(),
            client->remoteIP().toString().c_str());

            for (const auto &log : logs_buffer) {
                client->text(log);
            }
        break;
    case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
    case WS_EVT_DATA:
        break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    }
}