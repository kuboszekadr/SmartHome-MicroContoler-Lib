#include "WiFiManager.h"

Logger WiFiManager::logger = Logger("wifimanager");

wl_status_t WiFiManager::connect(const char *ssid, const char *pwd)
{
    WiFi.begin(ssid, pwd);
    WiFiManager::manageConnection();
    return WiFi.status();
}

void WiFiManager::manageConnection()
{
    // TODO: Cleanup
    wl_status_t status = WiFi.status();
    uint8_t timeout = 0;
    
    if (status != WL_CONNECTED)
    {
        logger.log("Connecting to WiFi");
    }

    while ((status != WL_CONNECTED) & (timeout < 10))
    {
        status = WiFi.status();
        Serial.print('.');

        if (status == WL_CONNECTED)
        {
            logger.log("Connected to target WiFi.");
        }

        timeout++; 
        delay(500);
    }

    if (
        status == WL_DISCONNECTED 
        || status == WL_CONNECT_FAILED
        || status == WL_CONNECTION_LOST)
    {
        timeout = 0;
        while (
            (WiFi.status() != WL_CONNECTED)
            & (timeout < 10))
        {
            WiFi.reconnect();
            timeout++;
            delay(500);
        }
    }

    if (status != WL_CONNECTED)
    {
        WiFi.disconnect();
        WiFi.reconnect();
    }

    if (status != WL_CONNECTED)
    {
        ESP.restart();
    }
}