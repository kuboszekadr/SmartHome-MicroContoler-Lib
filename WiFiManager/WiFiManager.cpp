#include "WiFiManager.h"

Logger WiFiManager::logger = Logger("wifimanager");

wl_status_t WiFiManager::connect(const char *ssid, const char *pwd)
{
    WiFi.begin(ssid, pwd);
    return WiFi.status();
}

void WiFiManager::manageConnection()
{
    wl_status_t status = WiFi.status();
    if (status != WL_CONNECTED)
    {
        Serial.println("Trying to reconnect...");
        status = WiFi.begin();

        if (status == WL_CONNECTED)
        {
            Serial.println("Connected to target WiFi.");
        }
        else
        {
            Serial.println("Reconnect failed...");
        }
    }
}