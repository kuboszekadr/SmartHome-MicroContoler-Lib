#include "Device.h"

SmartHomeDevice *Device::device;
Logger Device::logger = Logger("Device");

void Device::setupAPI()
{
    Config config = Config("api");
    config.load();

    String name = config.data["device_name"];
    device = new SmartHomeDevice(
        config.data["host"],
        config.data["port"].as<int>(),
        name);

    WiFi.setHostname(name.c_str());
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("Aquarium-Lighting");        
}

void Device::setupWiFi()
{
    Config config = Config("wifi");
    config.load();

    wl_status_t status = WiFiManager::connect(
        config.data["ssid"] | "Dummy",
        config.data["pwd"] | "Empty"
        );
}

void Device::setupTime()
{
    const char* ntpServer = "pool.ntp.org";
    configTime(3600, 3600, ntpServer);
    logger.log("Syncing time...");
    if (device == nullptr)
    {
        logger.log("Can not sync time with the server.");
        return;
    }

    // send request to host server
    JsonDocument doc;
    uint8_t timeout = 0;

    while (timeout < 10)
    {
        if (!device->sync(doc))
        {
            logger.log("Retrying to sync...");
        }
        else
        {
            break;
        }
        timeout += 1;
        delay(100);
    }

    long epoch = doc["date"];
    int timezone = doc["timezone"];

    char tz[10];
    if (timezone > 0)
    {
        sprintf(tz, "UTC-%i", timezone);
    }
    else
    {
        sprintf(tz, "UTC+%i", -timezone);
    }

    setTime(epoch, tz);
    logger.log("Time set sucessfully");
}

void Device::setupSPIFSS()
{
    if (!SPIFFS.begin())
    {
        logger.log("Failed to mount file system.");
    }
}

void Device::sendHeartbeat()
{
    JsonDocument doc;
    JsonObject obj = doc.to<JsonObject>();

    Serial.println("Sending heartbeat...");

    obj["device_name"] = device->device_name;
    (void)device->postData(obj, "api/v1.0/heartbeat");
}

void Device::setup()
{
    setupSPIFSS();
    setupWiFi();

    setupAPI();
    setupTime();
}

void Device::checkForUpdates()
{
    HTTPClient client;
    client.begin("http://74.234.8.4:5000/updates");
    client.setConnectTimeout(1000);

    int response_code = client.GET();
    if (response_code != 200)
    {
        logger.log("Could not check...");
    }

    JsonDocument doc;

    deserializeJson(doc, client.getString());
    serializeJsonPretty(doc, Serial);

    client.end();

    bool update_firmware = bool(doc["firmware"] == 1 | 0);
    bool update_filesystem = bool(doc["filesystem"] == 1 | 0);
    bool updated = false;

    httpUpdate.rebootOnUpdate(false);
    if (update_firmware)
    {
        delay(1000);
        updated = updateFirmware();
    }

    if (update_filesystem)
    {
        delay(1000);
        updated = (updated | updateFilesystem());
    }

    if (updated)
    {
        Serial.println("Filesystem or firmware has been updated. Restarting.");
        ESP.restart();
    }    
}


bool updateFirmware()
{
    Serial.println("Updating firmware...");

    WiFiClient client;

    const char *update_url = "http://74.234.8.4:5000/download_latest";
    t_httpUpdate_return ret = httpUpdate.update(client, update_url);

    bool result = false;

    switch (ret)
    {
    case HTTP_UPDATE_FAILED:
        Serial.printf(
            "HTTP_UPDATE_FAILED Error (%d): %s\n",
            httpUpdate.getLastError(),
            httpUpdate.getLastErrorString().c_str());
        break;

    case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");

        break;

    case HTTP_UPDATE_OK:
        result = true;
        Serial.println("HTTP_UPDATE_OK");

        break;
    }

    return result;
}

bool updateFilesystem()
{
    Serial.println("Updating filesystem image...");

    WiFiClient client;
    const char *update_url = "http://74.234.8.4:5000/download_latest_fs";
    t_httpUpdate_return ret = httpUpdate.updateSpiffs(client, update_url);
    bool result = false;

    switch (ret)
    {
    case HTTP_UPDATE_FAILED:
        Serial.printf(
            "HTTP_UPDATE_FAILD Error (%d): %s\n",
            httpUpdate.getLastError(),
            httpUpdate.getLastErrorString().c_str());
        break;

    case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;

    case HTTP_UPDATE_OK:
        result = true;
        Serial.println("HTTP_UPDATE_OK");
        break;
    }

    return result;
}