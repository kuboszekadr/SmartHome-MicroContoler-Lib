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
}

void Device::setupWiFi()
{
  WiFi.mode(WIFI_STA);

  Config config = Config("wifi");
  config.load();

  WiFiManager::connect(
      config.data["ssid"],
      config.data["pwd"]);
}

void Device::setupTime()
{
  logger.log("Syncing time...");
  if (device == nullptr)
  {
    logger.log("Can not sync time with the server.");
    return;
  }

  // send request to host server
  StaticJsonDocument<256> doc;
  device->sync(doc);

  long epoch = doc["date"];
  int timezone = doc["timezone"]; 

  // set device time
  ESP32Time _time = ESP32Time();
  _time.setTime(epoch);

  char tz[10];
  if (timezone > 0) // trial and fail obtained...
  {
    sprintf(tz, "UTC-%i", timezone);
  }
  else
  {
    sprintf(tz, "UTC+%i", -timezone);
  }
  setenv("TZ", tz, 0);
  tzset();

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
  StaticJsonDocument<128> doc;
  JsonObject obj = doc.to<JsonObject>();

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